#include "include/Input.hpp"

#include "include/Panic.hpp"

#include <cassert>
#include <iostream>

class Flow;

Input::Input(Flow* flow, Tensor input_tensor)
    : FlowNode({}, input_tensor, flow) {}

CtTensor Input::cipherfy(std::vector<CtTensor> parents) const {
    assert(parents.size() == 0);
    panic("cipherfy() should not be called on an `Input' instance");
    return parents[0];
}
