#include "include/Flow.hpp"

#include "include/Cipherfier.hpp"
#include "include/FlowNode.hpp"
#include "include/Input.hpp"
#include "include/Tensor.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

Input* Flow::input(Tensor input_tensor) {
    auto in_node =
        Input::create(dynamic_cast<Graph<FlowNode>*>(this), input_tensor);
    return in_node;
}

CtGraph* Flow::cipherfy() {
    Cipherfier cfv;
    for (auto& node : nodes_) {
        node->visit(&cfv);
    }
    return cfv.ct_graph();
}

