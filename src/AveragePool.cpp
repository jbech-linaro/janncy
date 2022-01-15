#include "include/AveragePool.hpp"

#include <utility>
#include <vector>

#include "include/FlowVisitor.hpp"
#include "include/KernelAttributes.hpp"

namespace janncy {

AveragePool::AveragePool(std::vector<int> input_shape, KernelAttributes kernel)
    : kernel_(std::move(kernel)),
      output_shape_(kernel_.output_shape(input_shape)) {}

void AveragePool::accept(FlowVisitor& visitor) { visitor.visit(*this); }
std::string AveragePool::op_type() const { return "AveragePool"; }
std::vector<int> AveragePool::shape() const { return output_shape_; }

const KernelAttributes& AveragePool::kernel() const { return kernel_; }

}  // namespace janncy
