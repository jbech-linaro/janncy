#include "include/ReLU.hpp"

#include <vector>

#include "include/FlowVisitor.hpp"

namespace janncy {

ReLU::ReLU(std::vector<int> shape) : shape_(std::move(shape)) {}

void ReLU::accept(FlowVisitor& visitor) { visitor.visit(*this); }
std::string ReLU::op_type() const { return "Relu"; }
std::vector<int> ReLU::shape() const { return shape_; }

}  // namespace janncy
