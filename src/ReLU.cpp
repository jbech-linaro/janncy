#include "include/ReLU.hpp"

#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"

#include <iostream>

ReLU::ReLU(FlowNode* parent) : FlowNode({parent}, parent->output_tensor()) {}

void ReLU::visit(FlowVisitor* visitor) { visitor->visit(this); }
