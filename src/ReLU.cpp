#include "include/ReLU.hpp"

#include "include/Flow.hpp"
#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"

#include <vector>

ReLU::ReLU(std::vector<int> output_shape) : FlowNode(output_shape, "Relu"){};

void ReLU::visit(Flow* flow, FlowVisitor* visitor) {
    visitor->visit(flow, this);
}
