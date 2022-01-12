#include "include/Add.hpp"

#include "include/Flow.hpp"
#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"

#include <vector>

namespace janncy {

Add::Add(std::vector<int> output_shape) : FlowNode(output_shape, "Add"){};

void Add::visit(Flow* flow, FlowVisitor* visitor) {
    visitor->visit(flow, this);
}

}  // namespace janncy
