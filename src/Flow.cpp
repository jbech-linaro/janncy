#include "include/Flow.hpp"

#include "include/CtGraph.hpp"
#include "include/CtInput.hpp"
#include "include/CtTensor.hpp"
#include "include/Input.hpp"
#include "include/Tensor.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

CtGraph* Flow::cipherfy() {
    CtGraph ct_graph;
    std::unordered_map<FlowNode*, CtTensor> ct_tensor_map;
    ct_tensor_map.insert(std::make_pair(
        sentinel(), CtTensor(std::vector<CtOp*>{ct_graph.sentinel()})));
    for (auto& node : nodes_) {
        std::vector<CtTensor> ct_parents;
        for (auto parent : node->get_parents()) {
            ct_parents.push_back(ct_tensor_map.at(parent));
        }
        ct_tensor_map.insert(std::make_pair(node, node->cipherfy(ct_parents)));
    }
    return new CtGraph(ct_graph);
}

Input* Flow::input(Tensor input_tensor) {
    auto in_node =
        Input::create(dynamic_cast<Graph<FlowNode>*>(this), input_tensor);
    return in_node;
}
