#include "include/cleartext_evaluator.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

#include "include/ct_add.h"
#include "include/ct_graph.h"
#include "include/ct_input.h"
#include "include/ct_mul.h"
#include "include/ct_op.h"
#include "include/ct_pt_add.h"
#include "include/ct_pt_mul.h"
#include "include/ct_rotate.h"
#include "include/message.h"

namespace janncy {

std::vector<Message> CleartextEvaluator::Evaluate(CtGraph& ct_graph,
                                                  std::vector<Message> inputs) {
  CleartextEvaluator clear_eval(ct_graph, inputs);
  for (CtOp* node : ct_graph.nodes()) {
    node->Accept(clear_eval);
  }
  return clear_eval.result();
}

void CleartextEvaluator::Visit(CtInput& node) {
  node_map_[&node] = inputs_.back();
  inputs_.pop_back();
}

void CleartextEvaluator::Visit(CtAdd& node) {
  auto p0 = node_map_[ct_graph_.parents(&node)[0]];
  auto p1 = node_map_[ct_graph_.parents(&node)[1]];
  std::transform(p0.begin(), p0.end(), p1.begin(),
                 std::back_inserter(node_map_[&node]),
                 std::plus<MessageElement>());
}

void CleartextEvaluator::Visit(CtMul& node) {
  auto p0 = node_map_[ct_graph_.parents(&node)[0]];
  auto p1 = node_map_[ct_graph_.parents(&node)[1]];
  std::transform(p0.begin(), p0.end(), p1.begin(),
                 std::back_inserter(node_map_[&node]),
                 std::multiplies<MessageElement>());
}

void CleartextEvaluator::Visit(CtRotate& node) {
  auto p = ct_graph_.parents(&node)[0];
  node_map_[&node] = node_map_[p];
  std::rotate(node_map_[&node].begin(), node_map_[&node].begin() + node.amt(),
              node_map_[&node].end());
}

void CleartextEvaluator::Visit(CtPtAdd& node) {
  auto p = node_map_[ct_graph_.parents(&node)[0]];
  std::transform(p.begin(), p.end(), node.value().begin(),
                 std::back_inserter(node_map_[&node]),
                 std::plus<MessageElement>());
}

void CleartextEvaluator::Visit(CtPtMul& node) {
  auto p = node_map_[ct_graph_.parents(&node)[0]];
  std::transform(p.begin(), p.end(), node.value().begin(),
                 std::back_inserter(node_map_[&node]),
                 std::multiplies<MessageElement>());
}

// TODO(nsamar): This function probably should not be public?
std::vector<Message> CleartextEvaluator::result() const {
  auto childless = std::vector<std::pair<CtOp*, Message>>();
  std::copy_if(
      node_map_.begin(), node_map_.end(), std::back_inserter(childless),
      [&](auto& x) { return ct_graph_.children(x.first).size() == 0; });
  auto result = std::vector<Message>();
  std::transform(childless.begin(), childless.end(), std::back_inserter(result),
                 [&](auto& x) { return x.second; });
  return result;
}

}  // namespace janncy
