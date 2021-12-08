#include "include/Input.hpp"

#include "include/Graph.hpp"
#include "include/Panic.hpp"

#include <cassert>
#include <iostream>

Input::Input(Graph<FlowNode>* flow, Tensor input_tensor)
    : FlowNode(flow, input_tensor) {}

CtTensor Input::cipherfy(std::vector<CtTensor> parents) const {
    assert(parents.size() == 0);
    panic("cipherfy() should not be called on an `Input' instance");
    return parents[0];
}
