#include "include/relu.h"

#include <string>
#include <vector>

#include "include/flow_visitor.h"

namespace janncy {

ReLU::ReLU(Shape shape) : shape_(std::move(shape)) {}

void ReLU::Accept(FlowVisitor& visitor) const { visitor.Visit(*this); }
std::string ReLU::op_type() const { return "Relu"; }
Shape ReLU::shape() const { return shape_; }

}  // namespace janncy
