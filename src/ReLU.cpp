#include "include/ReLU.hpp"

#include "include/FlowNode.hpp"

ReLU::ReLU(Tensor input_tensor) : FlowNode(input_tensor, input_tensor) {}
