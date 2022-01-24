#include "include/relu.h"

#include <string>
#include <vector>

#include "include/layer_visitor.h"

namespace janncy {

ReLU::ReLU(Shape shape) : shape_(std::move(shape)) {}

void ReLU::Accept(LayerVisitor& visitor) const { visitor.Visit(*this); }
std::string ReLU::op_type() const { return "Relu"; }
Shape ReLU::shape() const { return shape_; }

}  // namespace janncy
