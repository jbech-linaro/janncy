#include "include/relu_layer.h"

#include <string>
#include <vector>

#include "include/layer_visitor.h"

namespace janncy {

ReluLayer::ReluLayer(Shape shape) : shape_(std::move(shape)) {}

void ReluLayer::Accept(LayerVisitor& visitor) const { visitor.Visit(*this); }
std::string ReluLayer::op_type() const { return "Relu"; }
Shape ReluLayer::shape() const { return shape_; }

}  // namespace janncy
