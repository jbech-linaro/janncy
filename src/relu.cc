#include "include/relu.h"

#include <string>
#include <vector>

#include "include/flow_visitor.h"

namespace janncy {

ReLU::ReLU(std::vector<int> shape) : shape_(std::move(shape)) {}

void ReLU::Accept(FlowVisitor& visitor) { visitor.Visit(*this); }

std::string ReLU::op_type() const { return "Relu"; }

std::vector<int> ReLU::shape() const { return shape_; }

}  // namespace janncy
