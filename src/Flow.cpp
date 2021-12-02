#include "Flow.hpp"

#include "FlowNode.hpp"

#include <cassert>

void Flow::add_child(FlowNode* parent, FlowNode* child) {
    assert(parent->output_tensor() == child->input_tensor());
    children[parent].push_back(child);
}

