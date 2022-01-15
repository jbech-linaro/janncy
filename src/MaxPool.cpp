#include "include/MaxPool.hpp"

#include <vector>

#include "include/FlowVisitor.hpp"
#include "include/KernelAttributes.hpp"

namespace janncy {

MaxPool::MaxPool(std::vector<int> input_shape, KernelAttributes kernel)
    : kernel_(std::move(kernel)),
      output_shape_(kernel_.output_shape(input_shape)) {}

void MaxPool::accept(FlowVisitor& visitor) { visitor.visit(*this); }
std::string MaxPool::op_type() const { return "MaxPool"; }
std::vector<int> MaxPool::shape() const { return output_shape_; }

}  // namespace janncy
