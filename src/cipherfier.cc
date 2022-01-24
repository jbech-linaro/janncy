#include "include/cipherfier.h"

#include <algorithm>
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

#include "include/add.h"
#include "include/average_pool.h"
#include "include/batch_normalization.h"
#include "include/conv_layer.h"
#include "include/ct_dag.h"
#include "include/flatten.h"
#include "include/fully_connected.h"
#include "include/input.h"
#include "include/max_pool.h"
#include "include/neural_network.h"
#include "include/panic.h"
#include "include/relu.h"

namespace janncy {

static const std::string kAllKeysAddedStamp = "serkey/AllKeysAddedStamp";

CtDag Cipherfier::Cipherfy(const NeuralNetwork& nn) {
  Cipherfier cipherfier(nn);
  for (const Layer* node : nn.nodes()) {
    int old_dag_size = cipherfier.ct_dag_.nodes().size();
    std::cout << "Visiting " << node->op_type() << "(" << node << ") "
              << node->shape() << "; ";
    node->Accept(cipherfier);
    int new_dag_size = cipherfier.ct_dag_.nodes().size();
    std::cerr << "Added " << new_dag_size - old_dag_size << " nodes (total "
              << new_dag_size << ")";
    std::cerr << "; tensor size: "
              << cipherfier.tensor_map_.at(node).ciphertexts().size() << "\n";
  }
  return std::move(cipherfier.ct_dag_);
}

Cipherfier::Cipherfier(const NeuralNetwork& nn) : nn_(nn) {}

const CtTensor& Cipherfier::get_parent_tensor(const Layer& node) const {
  return get_parent_tensor(node, 0);
}
const CtTensor& Cipherfier::get_parent_tensor(const Layer& node,
                                              int parent_ind) const {
  return tensor_map_.at(nn_.parents(node)[parent_ind]);
}

const CtOp& SumCiphertexts(CtDag& ct_dag, const std::vector<const CtOp*>& cts) {
  assert(!cts.empty());
  if (cts.size() == 1) {
    return *cts[0];
  } else {
    auto cts_mid = cts.begin() + cts.size() / 2;
    std::vector<const CtOp*> first_half(cts.begin(), cts_mid);
    std::vector<const CtOp*> second_half(cts_mid, cts.end());

    return ct_dag::CreateAdd(ct_dag, SumCiphertexts(ct_dag, first_half),
                             SumCiphertexts(ct_dag, second_half));
  }
}

// slot i of result is the sum of ct[i:i + sum_length]
// Should also be doable with strides
const CtOp& PrefixSums(CtDag& ct_dag, const CtOp& ct, int sum_length) {
  int current_sum_length = 1;
  const CtOp* result = &ct;
  while (current_sum_length < sum_length) {
    int rotate_by =
        std::min(current_sum_length, sum_length - current_sum_length);
    current_sum_length += rotate_by;
    result = &ct_dag::CreateAdd(ct_dag, *result,
                                ct_dag::CreateRotate(ct_dag, *result));
  }
  assert(current_sum_length == sum_length);
  return *result;
}
// return a ct consisting of the first element from each of `cts`
// Assumes the remaining elements are all 0s
const CtOp& FlattenSlots(CtDag& ct_dag, const std::vector<const CtOp*>& cts) {
  std::vector<const CtOp*> slots;
  for (const CtOp* ct : cts) {
    slots.push_back(&ct_dag::CreateRotate(ct_dag, *ct));
  }
  return SumCiphertexts(ct_dag, slots);
}

const CtOp& ApplyFilter(CtDag& ct_dag, const CtTensor& input,
                        const KernelAttributes& kernel) {
  int kernel_size = 1;
  for (int d : kernel.kernel_shape()) {
    kernel_size *= d;
  }
  std::vector<const CtOp*> partial_filters;
  for (const CtOp* channel : input.ciphertexts()) {
    for (int i = 0; i < kernel_size; ++i) {
      const CtOp& rotated = ct_dag::CreateRotate(ct_dag, *channel);
      const CtOp& multiplied = ct_dag::CreatePtMul(ct_dag, rotated);
      partial_filters.push_back(&multiplied);
    }
  }
  return SumCiphertexts(ct_dag, partial_filters);
}

// return {ct^1, ct^2, ..., ct^degree}
std::vector<const CtOp*> CtPowers(CtDag& ct_dag, const CtOp& ct, int degree) {
  if (degree == 1) {
    return {&ct};
  }
  int low_degrees = (degree + 1) / 2;  // ceil(degree / 2)
  std::vector<const CtOp*> powers = CtPowers(ct_dag, ct, low_degrees);
  const CtOp& mid_power = *powers.back();
  for (int i = low_degrees; i < degree; ++i) {
    powers.push_back(
        &ct_dag::CreateMul(ct_dag, *powers[i - low_degrees], mid_power));
  }
  return powers;
}
const CtOp& PolyEval(CtDag& ct_dag, const CtOp& parent, int degree) {
  std::vector<const CtOp*> multiplied_powers;
  for (const CtOp* p : CtPowers(ct_dag, parent, degree)) {
    multiplied_powers.push_back(&ct_dag::CreatePtMul(ct_dag, *p));
  }
  const CtOp& summed_powers = SumCiphertexts(ct_dag, multiplied_powers);
  return ct_dag::CreatePtAdd(ct_dag,
                             summed_powers);  // add in constant factor
}
const CtOp& ReluPolynomial(CtDag& ct_dag, const CtOp& parent) {
  const CtOp& first_poly = PolyEval(ct_dag, parent, 16);
  const CtOp& second_poly = PolyEval(ct_dag, first_poly, 7);
  const CtOp& third_poly = PolyEval(ct_dag, second_poly, 7);
  return third_poly;
}

void Cipherfier::Visit(const ConvLayer& node) {
  const CtTensor& parent_tensor = get_parent_tensor(node);
  int output_channel_cnt = node.shape()[0];
  std::vector<const CtOp*> output_channels;
  for (int i = 0; i < output_channel_cnt; ++i) {
    output_channels.push_back(
        &ApplyFilter(ct_dag_, parent_tensor, node.kernel()));
  }
  tensor_map_.emplace(&node, CtTensor(std::move(output_channels)));
}

void Cipherfier::Visit(const AveragePool& node) {
  // TODO(alex): verify correctness and make it work for non-global Average
  // pool
  // TODO(alex): make it work for non 2D stuff (or explicitly decide not to
  // support
  //      them)
  // TODO(alex): this node is currently just bypassed
  CtTensor tensor = get_parent_tensor(node);  // copies parent tensor
  tensor_map_.emplace(&node, tensor);
}

void Cipherfier::Visit(const MaxPool& node) {
  // TODO(nsamar): this node is currently just bypassed
  CtTensor tensor = get_parent_tensor(node);  // copies parent tensor
  tensor_map_.emplace(&node, tensor);
}

void Cipherfier::Visit(const FullyConnected& node) {
  const CtTensor& parent_tensor = get_parent_tensor(node);
  PANIC_IF(parent_tensor.ciphertexts().size() != 1);
  const CtOp& input_ct = *parent_tensor.ciphertexts()[0];

  std::vector<const CtOp*> slots;
  for (int i = 0; i < node.output_size(); i++) {
    const CtOp& weighted_row = ct_dag::CreatePtMul(ct_dag_, input_ct);
    const CtOp& summed = PrefixSums(ct_dag_, weighted_row, node.input_size());
    const CtOp& masked = ct_dag::CreatePtMul(ct_dag_, summed);
    slots.push_back(&masked);
  }
  tensor_map_.emplace(&node, CtTensor({&FlattenSlots(ct_dag_, slots)}));
}

void Cipherfier::Visit(const Flatten& node) {
  // alex: Not super correct, but forces things into a single CT as expected
  // by FullyConnected
  const CtOp& result =
      FlattenSlots(ct_dag_, get_parent_tensor(node).ciphertexts());
  tensor_map_.emplace(&node, CtTensor({&result}));
}

void Cipherfier::Visit(const BatchNormalization& node) {
  const std::vector<const CtOp*>& par_cts =
      get_parent_tensor(node).ciphertexts();

  std::vector<const CtOp*> result;
  result.reserve(par_cts.size());
  std::transform(par_cts.begin(), par_cts.end(), std::back_inserter(result),
                 [this](const CtOp* ct) {
                   return &ct_dag::CreatePtMul(
                       ct_dag_, ct_dag::CreatePtAdd(ct_dag_, *ct));
                 });
  tensor_map_.emplace(&node, CtTensor(result));
}

void Cipherfier::Visit(const Add& node) {
  const std::vector<const CtOp*>& p0_cts =
      get_parent_tensor(node, 0).ciphertexts();
  const std::vector<const CtOp*>& p1_cts =
      get_parent_tensor(node, 1).ciphertexts();

  std::vector<const CtOp*> sum_cts(p0_cts.size());
  for (int i = 0; i < int(p0_cts.size()); ++i) {
    sum_cts[i] = &ct_dag::CreateAdd(ct_dag_, *p0_cts[i], *p1_cts[i]);
  }
  tensor_map_.emplace(&node, CtTensor(std::move(sum_cts)));
}

void Cipherfier::Visit(const Input& node) {
  int channel_cnt = node.shape()[0];
  std::vector<const CtOp*> input_cts;
  for (int i = 0; i < channel_cnt; ++i) {
    input_cts.push_back(&ct_dag::CreateInput(ct_dag_));
  }
  tensor_map_.emplace(&node, CtTensor(std::move(input_cts)));
}

void Cipherfier::Visit(const ReLU& node) {
  const CtTensor& parent_tensor = get_parent_tensor(node);
  std::vector<const CtOp*> output_cts;
  for (const CtOp* ct : parent_tensor.ciphertexts()) {
    output_cts.push_back(&ReluPolynomial(ct_dag_, *ct));
  }
  tensor_map_.emplace(&node, CtTensor(std::move(output_cts)));
}

}  // namespace janncy
