#include "include/Add.hpp"

Add::Add(FlowNode* parent0, FlowNode* parent1)
    : FlowNode({parent0, parent1}, parent0->output_tensor()) {}
