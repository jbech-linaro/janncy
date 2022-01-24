#include "include/add_layer.h"

#include <string>
#include <utility>
#include <vector>

#include "include/layer_visitor.h"

namespace janncy {

AddLayer::AddLayer(Shape shape) : shape_(std::move(shape)) {}

void AddLayer::Accept(LayerVisitor& visitor) const { visitor.Visit(*this); }
std::string AddLayer::op_type() const { return "Add"; }
Shape AddLayer::shape() const { return shape_; }

}  // namespace janncy
