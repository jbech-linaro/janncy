#include "include/add.h"

#include <string>
#include <utility>
#include <vector>

#include "include/flow_visitor.h"

namespace janncy {

Add::Add(Shape shape) : shape_(std::move(shape)) {}

void Add::Accept(FlowVisitor& visitor) const { visitor.Visit(*this); }
std::string Add::op_type() const { return "Add"; }
Shape Add::shape() const { return shape_; }

}  // namespace janncy
