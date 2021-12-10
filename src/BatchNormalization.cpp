#include "include/BatchNormalization.hpp"
#include "include/FlowVisitor.hpp"

BatchNormalization::BatchNormalization(FlowNode* parent)
    : FlowNode({parent}, parent->output_tensor()) {}

void BatchNormalization::visit(FlowVisitor* visitor) { visitor->visit(this); }
