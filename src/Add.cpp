#include "include/Add.hpp"

#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"

#include <vector>

Add::Add(FlowNode* parent0, FlowNode* parent1)
    : FlowNode({parent0, parent1}, parent0->output_tensor()) {}

void Add::visit(FlowVisitor* visitor) { visitor->visit(this); }
