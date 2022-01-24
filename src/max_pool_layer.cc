#include "include/max_pool_layer.h"

#include <vector>

#include "include/kernel_attributes.h"
#include "include/layer_visitor.h"

namespace janncy {

MaxPoolLayer::MaxPoolLayer(Shape input_shape, KernelAttributes kernel)
    : kernel_(std::move(kernel)),
      output_shape_(kernel_.output_shape(input_shape)) {}

void MaxPoolLayer::Accept(LayerVisitor& visitor) const { visitor.Visit(*this); }
std::string MaxPoolLayer::op_type() const { return "MaxPool"; }
Shape MaxPoolLayer::shape() const { return output_shape_; }

}  // namespace janncy
