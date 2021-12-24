#include "include/Flatten.hpp"

#include "include/Flow.hpp"
#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"

Flatten::Flatten(std::vector<int> output_shape)
    : FlowNode(output_shape, "Flatten") {}

void Flatten::visit(Flow* flow, FlowVisitor* visitor) {
    visitor->visit(flow, this);
}
