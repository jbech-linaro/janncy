#include "include/CleartextEvaluator.hpp"

#include <unordered_map>
#include <vector>

#include "include/CtAdd.hpp"
#include "include/CtInput.hpp"
#include "include/CtMul.hpp"
#include "include/CtOp.hpp"
#include "include/CtPtAdd.hpp"
#include "include/CtPtMul.hpp"
#include "include/CtRotate.hpp"

void CleartextEvaluator::visit(CtInput* node) {
    node_map_[node] = inputs_.back();
    inputs_.pop_back();
}

void CleartextEvaluator::visit(CtAdd* node) {
    auto p0 = node_map_[node->get_parents()[0]];
    auto p1 = node_map_[node->get_parents()[1]];
    std::transform(p0.begin(), p0.end(), p1.begin(),
                   std::back_inserter(node_map_[node]), std::plus<double>());
}

void CleartextEvaluator::visit(CtMul* node) {
    auto p0 = node_map_[node->get_parents()[0]];
    auto p1 = node_map_[node->get_parents()[1]];
    std::transform(p0.begin(), p0.end(), p1.begin(),
                   std::back_inserter(node_map_[node]),
                   std::multiplies<double>());
}

void CleartextEvaluator::visit(CtRotate* node) {
    auto p = node->get_parents()[0];
    node_map_[node] = node_map_[p];
    std::rotate(node_map_[node].begin(), node_map_[node].begin() + node->amt(),
                node_map_[node].end());
}

void CleartextEvaluator::visit(CtPtAdd* node) {
    auto p = node_map_[node->get_parents()[0]];
    std::transform(p.begin(), p.end(), node->value().begin(),
                   std::back_inserter(node_map_[node]), std::plus<double>());
}

void CleartextEvaluator::visit(CtPtMul* node) {
    auto p = node_map_[node->get_parents()[0]];
    std::transform(p.begin(), p.end(), node->value().begin(),
                   std::back_inserter(node_map_[node]),
                   std::multiplies<double>());
}

std::vector<std::vector<double> > CleartextEvaluator::result() const {
    auto childless = std::vector<std::pair<CtOp*, std::vector<double> > >();
    std::copy_if(node_map_.begin(), node_map_.end(),
                 std::back_inserter(childless),
                 [&](auto& x) { return x.first->get_children().size() == 0; });
    auto result = std::vector<std::vector<double> >();
    std::transform(childless.begin(), childless.end(),
                   std::back_inserter(result),
                   [&](auto& x) { return x.second; });
    return result;
}

