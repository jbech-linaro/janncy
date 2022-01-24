#include "include/max_pool.h"

#include <vector>

#include "include/kernel_attributes.h"
#include "include/layer_visitor.h"

namespace janncy {

MaxPool::MaxPool(Shape input_shape, KernelAttributes kernel)
    : kernel_(std::move(kernel)),
      output_shape_(kernel_.output_shape(input_shape)) {}

void MaxPool::Accept(LayerVisitor& visitor) const { visitor.Visit(*this); }
std::string MaxPool::op_type() const { return "MaxPool"; }
Shape MaxPool::shape() const { return output_shape_; }

}  // namespace janncy
