#include "include/input.h"

#include <utility>
#include <vector>

#include "include/flow.h"
#include "include/flow_visitor.h"
#include "include/graph.h"

namespace janncy {

Input::Input(std::vector<int> shape) : shape_(std::move(shape)) {}

void Input::Accept(FlowVisitor& visitor) const { visitor.Visit(*this); }
std::string Input::op_type() const { return "Input"; }
std::vector<int> Input::shape() const { return shape_; }

}  // namespace janncy
