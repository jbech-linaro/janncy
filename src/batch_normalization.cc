#include "include/batch_normalization.h"

#include <string>
#include <utility>
#include <vector>

#include "include/layer_visitor.h"

namespace janncy {

BatchNormalization::BatchNormalization(Shape shape)
    : shape_(std::move(shape)) {}

void BatchNormalization::Accept(LayerVisitor& visitor) const {
  visitor.Visit(*this);
}
std::string BatchNormalization::op_type() const { return "BatchNormalization"; }
Shape BatchNormalization::shape() const { return shape_; }

}  // namespace janncy
