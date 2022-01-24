#include "include/ciphertext_evaluator.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

#include "include/ciphertext.h"
#include "include/ct_add.h"
#include "include/ct_dag.h"
#include "include/ct_input.h"
#include "include/ct_mul.h"
#include "include/ct_op.h"
#include "include/ct_pt_add.h"
#include "include/ct_pt_mul.h"
#include "include/ct_rotate.h"

namespace janncy {

std::vector<Message> CiphertextEvaluator::Evaluate(
    const CtDag& ct_dag, std::vector<Message> inputs) {
  CiphertextEvaluator ct_eval(ct_dag, inputs);
  for (const CtOp* node : ct_dag.nodes()) {
    node->Accept(ct_eval);
  }
  return ct_eval.result();
}

CiphertextEvaluator::CiphertextEvaluator(const CtDag& ct_dag,
                                         std::vector<Message> inputs)
    : ct_dag_(ct_dag), inputs_(inputs){};

void CiphertextEvaluator::Visit(const CtInput& node) {
  auto in_ct = Ciphertext::Encrypt(inputs_.back());
  node_map_.emplace(&node, in_ct);
  inputs_.pop_back();
}

void CiphertextEvaluator::Visit(const CtAdd& node) {
  auto ct0 = node_map_.at(ct_dag_.parents(node)[0]);
  auto ct1 = node_map_.at(ct_dag_.parents(node)[1]);
  node_map_.emplace(&node, ct0.Add(ct1));
}

void CiphertextEvaluator::Visit(const CtMul& node) {
  auto ct0 = node_map_.at(ct_dag_.parents(node)[0]);
  auto ct1 = node_map_.at(ct_dag_.parents(node)[1]);
  node_map_.emplace(&node, ct0.Multiply(ct1));
}

void CiphertextEvaluator::Visit(const CtRotate& node) {
  auto parent_ct = node_map_.at(ct_dag_.parents(node)[0]);
  node_map_.emplace(&node, parent_ct.Rotate(node.amt()));
}

void CiphertextEvaluator::Visit(const CtPtAdd& node) {
  auto parent_ct = node_map_.at(ct_dag_.parents(node)[0]);
  Message pt_values(node.value().begin(), node.value().end());
  node_map_.emplace(&node, parent_ct.AddPtVec(pt_values));
}

void CiphertextEvaluator::Visit(const CtPtMul& node) {
  auto parent_ct = node_map_.at(ct_dag_.parents(node)[0]);
  Message pt_values(node.value().begin(), node.value().end());
  node_map_.emplace(&node, parent_ct.AddPtVec(pt_values));
}

// TODO(nsamar): This function probably should not be public?
std::vector<Message> CiphertextEvaluator::result() const {
  auto childless = std::vector<std::pair<const CtOp*, Ciphertext>>();
  std::copy_if(node_map_.begin(), node_map_.end(),
               std::back_inserter(childless),
               [&](auto& x) { return ct_dag_.children(*x.first).size() == 0; });
  auto result = std::vector<Message>();
  std::transform(childless.begin(), childless.end(), std::back_inserter(result),
                 [&](auto& x) { return x.second.Decrypt(); });
  return result;
}

}  // namespace janncy
