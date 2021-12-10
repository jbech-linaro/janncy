#include "include/FullyConnected.hpp"

#include "include/FlowVisitor.hpp"

#include <iostream>

FullyConnected::FullyConnected(FlowNode* parent, Tensor matrix)
    : FlowNode({parent}, Tensor({matrix.shape()[1]})) {}

void FullyConnected::visit(FlowVisitor* visitor) { visitor->visit(this); }
