#include "include/ConvLayer.hpp"

#include "include/Flow.hpp"
#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"

#include <vector>

ConvLayer::ConvLayer(std::vector<int> output_shape,
                     std::vector<int> kernel_shape, std::vector<int> stride,
                     std::vector<int> padding)
    : FlowNode(output_shape, "Conv"),
      kernel_shape_(kernel_shape),
      stride_(stride),
      padding_(padding){};

std::vector<int> ConvLayer::stride() const { return stride_; }
std::vector<int> ConvLayer::kernel_shape() const { return kernel_shape_; }
std::vector<int> ConvLayer::padding() const { return padding_; }

void ConvLayer::visit(Flow* flow, FlowVisitor* visitor) {
    visitor->visit(flow, this);
}
