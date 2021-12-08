#include "include/Flow.hpp"

#include "include/CtInput.hpp"
#include "include/Input.hpp"
#include "include/Tensor.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

CtGraph Flow::cipherfy() {
    CtGraph ct_graph;
    std::unordered_set<FlowNode*> frontier(nodes_);
    std::unordered_map<FlowNode*, CtTensor> ct_tensor_map;
    std::unordered_set<FlowNode*> visited;
    while (!frontier.empty()) {
        for (auto& node : frontier) {
            std::cout << node->output_tensor().shape()[0] << std::endl;
            auto parents = node->get_parents();
            if (parents.size() == 0) {
                std::vector<CtOp*> ct_tensor_vec(
                    node->output_tensor().shape()[0], ct_graph.input());
                std::cout << "Hello" << std::endl;
                ct_tensor_map.insert(
                    std::make_pair(node, CtTensor(ct_tensor_vec)));
                visited.insert(node);
                auto children = node->get_children();
            } else if (std::all_of(parents.begin(), parents.end(),
                                   [&](auto x) { return visited.count(x); })) {
                visited.insert(node);
                std::vector<CtTensor> ct_parents;
                for (auto parent : parents) {
                    std::cout << "Hello2" << std::endl;
                    ct_parents.push_back(ct_tensor_map.at(parent));
                }
                ct_tensor_map.insert(
                    std::make_pair(node, node->cipherfy(ct_parents)));
                auto children = node->get_children();
            }
        }
        std::unordered_set<FlowNode*> new_frontier;
        for (auto& node : frontier) {
            if (!visited.count(node)) {
                new_frontier.insert(node);
            } else {
                auto children = node->get_children();
                for (auto& child : children) {
                    new_frontier.insert(child);
                }
            }
        }
        frontier = new_frontier;
    }
    return ct_graph;
}

Input* Flow::input(Tensor input_tensor) {
    auto in_node = Input::create(this, input_tensor);
    add_node(in_node);
    return in_node;
}
