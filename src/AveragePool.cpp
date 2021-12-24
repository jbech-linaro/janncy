#include "include/AveragePool.hpp"

#include "include/Flow.hpp"
#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"

#include <vector>

AveragePool::AveragePool(std::vector<int> output_shape,
                         std::vector<int> kernel_shape, std::vector<int> stride,
                         std::vector<int> padding)
    : FlowNode(output_shape, "AveragePool"),
      kernel_shape_(kernel_shape),
      stride_(stride),
      padding_(padding){};

void AveragePool::visit(Flow* flow, FlowVisitor* visitor) {
    visitor->visit(flow, this);
}

std::vector<int> AveragePool::stride() const { return stride_; }
std::vector<int> AveragePool::padding() const { return padding_; }
std::vector<int> AveragePool::kernel_shape() const { return kernel_shape_; }

