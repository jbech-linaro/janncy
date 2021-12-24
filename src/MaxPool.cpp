#include "include/MaxPool.hpp"

#include "include/Flow.hpp"
#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"

#include <vector>

MaxPool::MaxPool(std::vector<int> output_shape, std::vector<int> kernel_shape,
                 std::vector<int> stride, std::vector<int> padding)
    : FlowNode(output_shape, "MaxPool"),
      kernel_shape_(kernel_shape),
      stride_(stride),
      padding_(padding){};

std::vector<int> MaxPool::stride() const { return stride_; }
std::vector<int> MaxPool::padding() const { return padding_; }
std::vector<int> MaxPool::kernel_shape() const { return kernel_shape_; }

void MaxPool::visit(Flow* flow, FlowVisitor* visitor) {
    visitor->visit(flow, this);
}
