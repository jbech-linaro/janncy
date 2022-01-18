#include "include/ciphertext_evaluator.h"

#include <algorithm>
#include <complex>
#include <unordered_map>
#include <vector>

#include "include/ciphertext.h"
#include "include/ct_add.h"
#include "include/ct_graph.h"
#include "include/ct_input.h"
#include "include/ct_mul.h"
#include "include/ct_op.h"
#include "include/ct_pt_add.h"
#include "include/ct_pt_mul.h"
#include "include/ct_rotate.h"

namespace janncy {

std::vector<std::vector<std::complex<double>>> CiphertextEvaluator::Evaluate(
    CtGraph& ct_graph, std::vector<std::vector<std::complex<double>>> inputs) {
  CiphertextEvaluator ct_eval(ct_graph, inputs);
  for (CtOp* node : ct_graph.nodes()) {
    node->Accept(ct_eval);
  }
  return ct_eval.result();
}

CiphertextEvaluator::CiphertextEvaluator(
    CtGraph& ct_graph, std::vector<std::vector<std::complex<double>>> inputs)
    : ct_graph_(ct_graph), inputs_(inputs){};

void CiphertextEvaluator::Visit(CtInput& node) {
  auto in_ct = Encrypt(inputs_.back());
  node_map_.emplace(&node, in_ct);
  inputs_.pop_back();
}

void CiphertextEvaluator::Visit(CtAdd& node) {
  auto ct0 = node_map_.at(ct_graph_.parents(&node)[0]);
  auto ct1 = node_map_.at(ct_graph_.parents(&node)[1]);
  node_map_.emplace(&node, ct0 + ct1);
}

void CiphertextEvaluator::Visit(CtMul& node) {
  auto ct0 = node_map_.at(ct_graph_.parents(&node)[0]);
  auto ct1 = node_map_.at(ct_graph_.parents(&node)[1]);
  node_map_.emplace(&node, ct0 * ct1);
}

void CiphertextEvaluator::Visit(CtRotate& node) {
  auto parent_ct = node_map_.at(ct_graph_.parents(&node)[0]);
  node_map_.emplace(&node, parent_ct.Rotate(node.amt()));
}

void CiphertextEvaluator::Visit(CtPtAdd& node) {
  auto parent_ct = node_map_.at(ct_graph_.parents(&node)[0]);
  std::vector<std::complex<double>> pt_values(node.value().begin(),
                                              node.value().end());
  node_map_.emplace(&node, parent_ct.AddPtVec(pt_values));
}

void CiphertextEvaluator::Visit(CtPtMul& node) {
  auto parent_ct = node_map_.at(ct_graph_.parents(&node)[0]);
  std::vector<std::complex<double>> pt_values(node.value().begin(),
                                              node.value().end());
  node_map_.emplace(&node, parent_ct.AddPtVec(pt_values));
}

// TODO(nsamar): This function probably should not be public?
std::vector<std::vector<std::complex<double>>> CiphertextEvaluator::result()
    const {
  auto childless = std::vector<std::pair<CtOp*, Ciphertext>>();
  std::copy_if(
      node_map_.begin(), node_map_.end(), std::back_inserter(childless),
      [&](auto& x) { return ct_graph_.children(x.first).size() == 0; });
  auto result = std::vector<std::vector<std::complex<double>>>();
  std::transform(childless.begin(), childless.end(), std::back_inserter(result),
                 [&](auto& x) { return x.second.Decrypt(); });
  return result;
}

}  // namespace janncy
