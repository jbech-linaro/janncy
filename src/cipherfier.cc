#include "include/cipherfier.h"

#include <unordered_map>
#include <vector>

#include "include/add.h"
#include "include/average_pool.h"
#include "include/batch_normalization.h"
#include "include/conv_layer.h"
#include "include/ct_graph.h"
#include "include/flatten.h"
#include "include/flow.h"
#include "include/fully_connected.h"
#include "include/input.h"
#include "include/max_pool.h"
#include "include/ostream_utils.h"
#include "include/panic.h"
#include "include/relu.h"

namespace janncy {

CtGraph Cipherfier::Cipherfy(Flow& flow) {
  Cipherfier cipherfier(flow);
  for (FlowNode* node : flow.nodes()) {
    int old_graph_size = cipherfier.ct_graph_.nodes().size();
    std::cout << "Visiting " << node->op_type() << "(" << node << ") "
              << node->shape() << "; ";
    node->Accept(cipherfier);
    int new_graph_size = cipherfier.ct_graph_.nodes().size();
    std::cerr << "Added " << new_graph_size - old_graph_size << " nodes (total "
              << new_graph_size << ")";
    std::cerr << "; tensor size: "
              << cipherfier.tensor_map_.at(node).ciphertexts().size() << "\n";
  }
  return std::move(cipherfier.ct_graph_);
}

Cipherfier::Cipherfier(Flow& flow) : flow_(flow) {}

const CtTensor& Cipherfier::get_parent_tensor(const FlowNode& node) const {
  return get_parent_tensor(node, 0);
}
const CtTensor& Cipherfier::get_parent_tensor(const FlowNode& node,
                                              int parent_ind) const {
  return tensor_map_.at(flow_.parents(&node)[parent_ind]);
}

const CtOp* Cipherfier::SumCiphertexts(const std::vector<const CtOp*>& cts) {
  assert(!cts.empty());
  if (cts.size() == 1) {
    return cts[0];
  } else {
    auto cts_mid = cts.begin() + cts.size() / 2;
    std::vector<const CtOp*> first_half(cts.begin(), cts_mid);
    std::vector<const CtOp*> second_half(cts_mid, cts.end());

    return ct_graph_.CreateAdd(SumCiphertexts(first_half),
                               SumCiphertexts(second_half));
  }
}
const CtOp* Cipherfier::PrefixSums(const CtOp* ct, int sum_length) {
  int current_sum_length = 1;
  while (current_sum_length < sum_length) {
    int rotate_by =
        std::min(current_sum_length, sum_length - current_sum_length);
    current_sum_length += rotate_by;
    ct = ct_graph_.CreateAdd(ct, ct_graph_.CreateRotate(ct));
  }
  assert(current_sum_length == sum_length);
  return ct;
}
const CtOp* Cipherfier::FlattenSlots(const std::vector<const CtOp*>& cts) {
  std::vector<const CtOp*> slots;
  for (const CtOp* ct : cts) {
    slots.push_back(ct_graph_.CreateRotate(ct));
  }
  return SumCiphertexts(slots);
}

const CtOp* Cipherfier::ApplyFilter(const CtTensor& input,
                                    const KernelAttributes& kernel) {
  int kernel_size = 1;
  for (int d : kernel.kernel_shape()) {
    kernel_size *= d;
  }
  std::vector<const CtOp*> partial_filters;
  for (const CtOp* channel : input.ciphertexts()) {
    for (int i = 0; i < kernel_size; ++i) {
      CtOp* rotated = ct_graph_.CreateRotate(channel);
      CtOp* multiplied = ct_graph_.CreatePtMul(rotated);
      partial_filters.push_back(multiplied);
    }
  }
  return SumCiphertexts(partial_filters);
}

std::vector<const CtOp*> Cipherfier::CtPowers(const CtOp* ct, int degree) {
  if (degree == 1) {
    return {ct};
  }
  int low_degrees = (degree + 1) / 2;  // ceil(degree / 2)
  std::vector<const CtOp*> powers = CtPowers(ct, low_degrees);
  const CtOp* mid_power = powers.back();
  for (int i = low_degrees; i < degree; ++i) {
    powers.push_back(ct_graph_.CreateMul(powers[i - low_degrees], mid_power));
  }
  return powers;
}
const CtOp* Cipherfier::PolyEval(const CtOp* parent, int degree) {
  std::vector<const CtOp*> multiplied_powers;
  for (const CtOp* p : CtPowers(parent, degree)) {
    multiplied_powers.push_back(ct_graph_.CreatePtMul(p));
  }
  const CtOp* summed_powers = SumCiphertexts(multiplied_powers);
  return ct_graph_.CreatePtAdd(summed_powers);  // add in constant factor
}
const CtOp* Cipherfier::ReluPolynomial(CtGraph& ct_graph, const CtOp* parent) {
  const CtOp* first_poly = PolyEval(parent, 16);
  const CtOp* second_poly = PolyEval(first_poly, 7);
  const CtOp* third_poly = PolyEval(second_poly, 7);
  return third_poly;
}

void Cipherfier::Visit(ConvLayer& node) {
  const CtTensor& parent_tensor = get_parent_tensor(node);
  int output_channel_cnt = node.shape()[0];
  std::vector<const CtOp*> output_channels;
  for (int i = 0; i < output_channel_cnt; ++i) {
    output_channels.push_back(ApplyFilter(parent_tensor, node.kernel()));
  }
  tensor_map_.emplace(&node, CtTensor(std::move(output_channels)));
}

void Cipherfier::Visit(AveragePool& node) {
  // TODO(alex): verify correctness and make it work for non-global Average pool
  // TODO(alex): make it work for non 2D stuff (or explicitly decide not to
  // support
  //      them)
  // TODO(alex): this node is currently just bypassed
  CtTensor tensor = get_parent_tensor(node);  // copies parent tensor
  tensor_map_.emplace(&node, tensor);

  /*
  std::vector<const CtOp*> result;
  // TODO using floats / double can cause weird errors
  auto amt = std::log2(node->kernel_shape()[1]);
  std::transform(
      parent.begin(), parent.end(), std::back_inserter(result), [&](auto x) {
          return accumulate(ct_graph_,
                  create_many(ct_graph_, amt, ct_rotate(ct_graph_, x)));
      });
  std::transform(parent.begin(), parent.end(), result.begin(),
      [&](auto x) {
          return accumulate(ct_graph_,
                        create_many(ct_graph_, amt, ct_rotate(ct_graph_, x)));
  });
  register_node(node, result);
  */
}

void Cipherfier::Visit(MaxPool& node) {
  // TODO(nsamar): this node is currently just bypassed
  CtTensor tensor = get_parent_tensor(node);  // copies parent tensor
  tensor_map_.emplace(&node, tensor);
}

void Cipherfier::Visit(FullyConnected& node) {
  const CtTensor& parent_tensor = get_parent_tensor(node);
  PANIC_IF(parent_tensor.ciphertexts().size() != 1);
  const CtOp* input_ct = parent_tensor.ciphertexts()[0];

  std::vector<const CtOp*> slots;
  for (int i = 0; i < node.output_size(); i++) {
    const CtOp* weighted_row = ct_graph_.CreatePtMul(input_ct);
    const CtOp* summed = PrefixSums(weighted_row, node.input_size());
    const CtOp* masked = ct_graph_.CreatePtMul(summed);
    slots.push_back(masked);
  }
  tensor_map_.emplace(&node, CtTensor({FlattenSlots(slots)}));
}

void Cipherfier::Visit(Flatten& node) {
  // alex: Not super correct, but forces things into a single CT as expected
  // by FullyConnected
  const CtOp* result = FlattenSlots(get_parent_tensor(node).ciphertexts());
  tensor_map_.emplace(&node, CtTensor({result}));
}

void Cipherfier::Visit(BatchNormalization& node) {
  std::vector<const CtOp*> result;
  for (const CtOp* ct : get_parent_tensor(node).ciphertexts()) {
    result.push_back(ct_graph_.CreatePtMul(ct_graph_.CreatePtAdd(ct)));
  }
  tensor_map_.emplace(&node, CtTensor(result));
}

void Cipherfier::Visit(Add& node) {
  const std::vector<const CtOp*>& p0_cts =
      get_parent_tensor(node, 0).ciphertexts();
  const std::vector<const CtOp*>& p1_cts =
      get_parent_tensor(node, 1).ciphertexts();

  std::vector<const CtOp*> sum_cts(p0_cts.size());
  for (int i = 0; i < int(p0_cts.size()); ++i) {
    sum_cts[i] = ct_graph_.CreateAdd(p0_cts[i], p1_cts[i]);
  }
  tensor_map_.emplace(&node, CtTensor(std::move(sum_cts)));
}

void Cipherfier::Visit(Input& node) {
  int channel_cnt = node.shape()[0];
  std::vector<const CtOp*> input_cts;
  for (int i = 0; i < channel_cnt; ++i) {
    input_cts.push_back(ct_graph_.CreateInput());
  }
  tensor_map_.emplace(&node, CtTensor(std::move(input_cts)));
}

void Cipherfier::Visit(ReLU& node) {
  const CtTensor& parent_tensor = get_parent_tensor(node);
  std::vector<const CtOp*> output_cts;
  for (const CtOp* ct : parent_tensor.ciphertexts()) {
    output_cts.push_back(ReluPolynomial(ct_graph_, ct));
  }
  tensor_map_.emplace(&node, CtTensor(std::move(output_cts)));
}

}  // namespace janncy
