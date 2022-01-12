#include "include/FullyConnected.hpp"

#include "include/Flow.hpp"
#include "include/FlowVisitor.hpp"

namespace janncy {

FullyConnected::FullyConnected(std::vector<int> output_shape)
    : FlowNode(output_shape, "FullyConnected") {}

void FullyConnected::visit(Flow* flow, FlowVisitor* visitor) {
    visitor->visit(flow, this);
}

}  // namespace janncy
