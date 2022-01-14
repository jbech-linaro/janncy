#include "include/BatchNormalization.hpp"

#include <vector>
#include <utility>

#include "include/FlowVisitor.hpp"

namespace janncy {

BatchNormalization::BatchNormalization(std::vector<int> shape)
    : shape_(std::move(shape)) {}

void BatchNormalization::accept(FlowVisitor &visitor) { visitor.visit(*this); }
std::string BatchNormalization::op_type() const { return "BatchNormalization"; }
std::vector<int> BatchNormalization::shape() const { return shape_; }

}  // namespace janncy
