#include "include/ConvLayer.hpp"

#include <vector>
#include <utility>

#include "include/FlowVisitor.hpp"
#include "include/KernelAttributes.hpp"

namespace janncy {

ConvLayer::ConvLayer(std::vector<int> input_shape,
                     KernelAttributes kernel, int output_ch)
        : kernel_(std::move(kernel)),
          output_shape_(kernel_.output_shape(input_shape, output_ch)) {}

void ConvLayer::accept(FlowVisitor& visitor) { visitor.visit(*this); }
std::string ConvLayer::op_type() const { return "Conv"; }
std::vector<int> ConvLayer::shape() const { return output_shape_; }

const KernelAttributes& ConvLayer::kernel() const { return kernel_; }

}  // namespace janncy
