#include "include/BatchNormalization.hpp"

#include "include/Flow.hpp"
#include "include/FlowVisitor.hpp"

BatchNormalization::BatchNormalization(std::vector<int> output_shape)
    : FlowNode(output_shape, "BatchNormalization"){};

void BatchNormalization::visit(Flow* flow, FlowVisitor* visitor) {
    visitor->visit(flow, this);
}
