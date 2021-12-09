#include "include/Input.hpp"

#include "include/CtInput.hpp"
#include "include/CtOp.hpp"
#include "include/Graph.hpp"
#include "include/Panic.hpp"

#include <cassert>
#include <iostream>

Input::Input(Graph<FlowNode>* flow, Tensor input_tensor)
    : FlowNode(flow, input_tensor) {}

CtTensor Input::cipherfy(std::vector<CtTensor> parents) const {
    std::vector<CtOp*> result;
    auto graph = parents[0].get_ct_ops()[0]->graph();
    for (int i = 0; i < output_tensor().shape()[0]; ++i) {
        result.push_back(new CtInput(graph));
    }
    return CtTensor(result);
}
