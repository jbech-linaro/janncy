#include "include/Add.hpp"

#include <vector>
#include <utility>

#include "include/FlowVisitor.hpp"

namespace janncy {

Add::Add(std::vector<int> shape) : shape_(std::move(shape)) {}

void Add::accept(FlowVisitor& visitor) { visitor.visit(*this); }
std::vector<int> Add::shape() const { return shape_; }
std::string Add::op_type() const { return "Add"; }

}  // namespace janncy
