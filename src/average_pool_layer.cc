#include "include/average_pool_layer.h"

#include <string>
#include <utility>
#include <vector>

#include "include/kernel_attributes.h"
#include "include/layer_visitor.h"

namespace janncy {

AveragePoolLayer::AveragePoolLayer(Shape input_shape, KernelAttributes kernel)
    : kernel_(std::move(kernel)),
      output_shape_(kernel_.output_shape(input_shape)) {}

void AveragePoolLayer::Accept(LayerVisitor& visitor) const {
  visitor.Visit(*this);
}
std::string AveragePoolLayer::op_type() const { return "AveragePool"; }
Shape AveragePoolLayer::shape() const { return output_shape_; }

const KernelAttributes& AveragePoolLayer::kernel() const { return kernel_; }

}  // namespace janncy
