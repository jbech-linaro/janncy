#include "include/ReLU.hpp"

#include "include/FlowNode.hpp"

ReLU::ReLU(FlowNode* parent) : FlowNode({parent}, parent->output_tensor()) {}
