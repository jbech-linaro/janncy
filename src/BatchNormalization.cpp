#include "include/BatchNormalization.hpp"

BatchNormalization::BatchNormalization(FlowNode* parent)
    : FlowNode({parent}, parent->output_tensor()) {}
