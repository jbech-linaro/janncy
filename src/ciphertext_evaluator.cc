#include "include/ciphertext_evaluator.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

#include "include/add_cc.h"
#include "include/add_cp.h"
#include "include/add_cs.h"
#include "include/ciphertext.h"
#include "include/ct_dag.h"
#include "include/ct_input.h"
#include "include/ct_op.h"
#include "include/message.h"
#include "include/mul_cc.h"
#include "include/mul_cp.h"
#include "include/mul_cs.h"
#include "include/rotate_c.h"

namespace janncy {

std::vector<Message::Vector> CiphertextEvaluator::Evaluate(
    const CtDag& ct_dag, std::vector<Message::Vector> inputs) {
  CiphertextEvaluator ct_eval(ct_dag, inputs);
  for (const CtOp* node : ct_dag.nodes()) {
    node->Accept(ct_eval);
  }
  return ct_eval.result();
}

CiphertextEvaluator::CiphertextEvaluator(const CtDag& ct_dag,
                                         std::vector<Message::Vector> inputs)
    : ct_dag_(ct_dag), inputs_(inputs){};

void CiphertextEvaluator::Visit(const CtInput& node) {
  auto in_ct = Ciphertext::Encrypt(inputs_.back());
  node_map_.emplace(&node, in_ct);
  inputs_.pop_back();
}

void CiphertextEvaluator::Visit(const AddCC& node) {
  auto ct0 = node_map_.at(ct_dag_.parents(node)[0]);
  auto ct1 = node_map_.at(ct_dag_.parents(node)[1]);
  node_map_.emplace(&node, ct0.AddCC(ct1));
}

void CiphertextEvaluator::Visit(const AddCP& node) {
  auto parent_ct = node_map_.at(ct_dag_.parents(node)[0]);
  auto message = message_evaluator_.evaluate(node.message());
  node_map_.emplace(&node, parent_ct.AddCP(message));
}

void CiphertextEvaluator::Visit(const AddCS& node) {
  auto ct0 = node_map_.at(ct_dag_.parents(node)[0]);
  node_map_.emplace(&node, ct0.AddCS(node.scalar()));
}

void CiphertextEvaluator::Visit(const MulCC& node) {
  auto ct0 = node_map_.at(ct_dag_.parents(node)[0]);
  auto ct1 = node_map_.at(ct_dag_.parents(node)[1]);
  node_map_.emplace(&node, ct0.MulCC(ct1));
}

void CiphertextEvaluator::Visit(const MulCP& node) {
  auto parent_ct = node_map_.at(ct_dag_.parents(node)[0]);
  auto message = message_evaluator_.evaluate(node.message());
  node_map_.emplace(&node, parent_ct.MulCP(message));
}

void CiphertextEvaluator::Visit(const MulCS& node) {
  auto ct0 = node_map_.at(ct_dag_.parents(node)[0]);
  node_map_.emplace(&node, ct0.MulCS(node.scalar()));
}

void CiphertextEvaluator::Visit(const RotateC& node) {
  auto parent_ct = node_map_.at(ct_dag_.parents(node)[0]);
  node_map_.emplace(&node, parent_ct.RotateC(node.amt()));
}

// TODO(nsamar): This function probably should not be public?
std::vector<Message::Vector> CiphertextEvaluator::result() const {
  auto childless = std::vector<std::pair<const CtOp*, Ciphertext>>();
  std::copy_if(node_map_.begin(), node_map_.end(),
               std::back_inserter(childless),
               [&](auto& x) { return ct_dag_.children(*x.first).size() == 0; });
  auto result = std::vector<Message::Vector>{};
  std::transform(childless.begin(), childless.end(), std::back_inserter(result),
                 [&](auto& x) { return x.second.Decrypt(); });
  return result;
}

}  // namespace janncy
