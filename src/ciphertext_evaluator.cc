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

void CiphertextEvaluator::visit(CtGraph* ct_graph, CtInput* node) {
  auto in_ct = encrypt(inputs_.back());
  node_map_.insert(std::make_pair(node, in_ct));
  inputs_.pop_back();
}

void CiphertextEvaluator::visit(CtGraph* ct_graph, CtAdd* node) {
  auto ct0 = node_map_.at(ct_graph->parents(node)[0]);
  auto ct1 = node_map_.at(ct_graph->parents(node)[1]);
  node_map_.insert(std::make_pair(node, ct0 + ct1));
}

void CiphertextEvaluator::visit(CtGraph* ct_graph, CtMul* node) {
  auto ct0 = node_map_.at(ct_graph->parents(node)[0]);
  auto ct1 = node_map_.at(ct_graph->parents(node)[1]);
  node_map_.insert(std::make_pair(node, ct0 * ct1));
}

void CiphertextEvaluator::visit(CtGraph* ct_graph, CtRotate* node) {
  auto parent_ct = node_map_.at(ct_graph->parents(node)[0]);
  node_map_.insert(std::make_pair(node, parent_ct.rotate(node->amt())));
}

void CiphertextEvaluator::visit(CtGraph* ct_graph, CtPtAdd* node) {
  auto parent_ct = node_map_.at(ct_graph->parents(node)[0]);
  std::vector<std::complex<double>> pt_values(node->value().begin(),
                                              node->value().end());
  node_map_.insert(std::make_pair(node, parent_ct.addPtVec(pt_values)));
}

void CiphertextEvaluator::visit(CtGraph* ct_graph, CtPtMul* node) {
  auto parent_ct = node_map_.at(ct_graph->parents(node)[0]);
  std::vector<std::complex<double>> pt_values(node->value().begin(),
                                              node->value().end());
  node_map_.insert(std::make_pair(node, parent_ct.addPtVec(pt_values)));
}

std::vector<std::vector<std::complex<double>>> CiphertextEvaluator::result(
    CtGraph* ct_graph) const {
  auto childless = std::vector<std::pair<CtOp*, Ciphertext>>();
  std::copy_if(
      node_map_.begin(), node_map_.end(), std::back_inserter(childless),
      [&](auto& x) { return ct_graph->children(x.first).size() == 0; });
  auto result = std::vector<std::vector<std::complex<double>>>();
  std::transform(childless.begin(), childless.end(), std::back_inserter(result),
                 [&](auto& x) { return x.second.decrypt(); });
  return result;
}

}  // namespace janncy
