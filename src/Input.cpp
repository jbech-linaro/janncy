#include "include/Input.hpp"

#include "include/FlowVisitor.hpp"
#include "include/Graph.hpp"

#include <cassert>
#include <iostream>

Input::Input(Graph<FlowNode>* flow, Tensor input_tensor)
    : FlowNode(flow, input_tensor) {}

void Input::visit(FlowVisitor* visitor) { visitor->visit(this); }
