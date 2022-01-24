#include "include/batch_normalization_layer.h"

#include <string>
#include <utility>
#include <vector>

#include "include/layer_visitor.h"

namespace janncy {

BatchNormalizationLayer::BatchNormalizationLayer(Shape shape)
    : shape_(std::move(shape)) {}

void BatchNormalizationLayer::Accept(LayerVisitor& visitor) const {
  visitor.Visit(*this);
}
std::string BatchNormalizationLayer::op_type() const {
  return "BatchNormalization";
}
Shape BatchNormalizationLayer::shape() const { return shape_; }

}  // namespace janncy
