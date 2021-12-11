#include "include/CtGraph.hpp"

#include "include/CleartextEvaluator.hpp"

#include <vector>

std::vector<std::vector<double>> CtGraph::evaluate(
    std::vector<std::vector<double>> init_values) {
    CleartextEvaluator eval(init_values);
    for (auto& node : nodes_) {
        node->visit(&eval);
    }
    return eval.result();
}
