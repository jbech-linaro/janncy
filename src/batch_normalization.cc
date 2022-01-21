#include "include/batch_normalization.h"

#include <string>
#include <utility>
#include <vector>

#include "include/flow_visitor.h"

namespace janncy {

BatchNormalization::BatchNormalization(std::vector<int> shape)
    : shape_(std::move(shape)) {}

void BatchNormalization::Accept(FlowVisitor& visitor) const {
  visitor.Visit(*this);
}
std::string BatchNormalization::op_type() const { return "BatchNormalization"; }
std::vector<int> BatchNormalization::shape() const { return shape_; }

}  // namespace janncy
