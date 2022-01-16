#include "include/batch_normalization.h"

#include <utility>
#include <vector>

#include "include/flow_visitor.h"

namespace janncy {

BatchNormalization::BatchNormalization(std::vector<int> shape)
    : shape_(std::move(shape)) {}

void BatchNormalization::accept(FlowVisitor &visitor) { visitor.visit(*this); }
std::string BatchNormalization::op_type() const { return "BatchNormalization"; }
std::vector<int> BatchNormalization::shape() const { return shape_; }

}  // namespace janncy
