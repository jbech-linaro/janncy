#include "include/add.h"

#include <string>
#include <utility>
#include <vector>

#include "include/flow_visitor.h"

namespace janncy {

Add::Add(std::vector<int> shape) : shape_(std::move(shape)) {}

void Add::Accept(FlowVisitor& visitor) const { visitor.Visit(*this); }
std::vector<int> Add::shape() const { return shape_; }
std::string Add::op_type() const { return "Add"; }

}  // namespace janncy
