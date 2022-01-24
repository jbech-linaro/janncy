#include "include/conv_layer.h"

#include <utility>
#include <vector>

#include "include/kernel_attributes.h"
#include "include/layer_visitor.h"

namespace janncy {

ConvLayer::ConvLayer(Shape input_shape, KernelAttributes kernel, int output_ch)
    : kernel_(std::move(kernel)),
      output_shape_(kernel_.output_shape(input_shape, output_ch)) {}

void ConvLayer::Accept(LayerVisitor& visitor) const { visitor.Visit(*this); }
std::string ConvLayer::op_type() const { return "Conv"; }
Shape ConvLayer::shape() const { return output_shape_; }

const KernelAttributes& ConvLayer::kernel() const { return kernel_; }

}  // namespace janncy
