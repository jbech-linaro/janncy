#include "include/Input.hpp"

#include "include/Flow.hpp"
#include "include/FlowVisitor.hpp"
#include "include/Graph.hpp"

#include <vector>

Input::Input(std::vector<int> input_shape) : FlowNode(input_shape, "Input") {}

void Input::visit(Flow* flow, FlowVisitor* visitor) {
    visitor->visit(flow, this);
}
