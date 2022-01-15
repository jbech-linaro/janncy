#include "include/Input.hpp"

#include <utility>
#include <vector>

#include "include/Flow.hpp"
#include "include/FlowVisitor.hpp"
#include "include/Graph.hpp"

namespace janncy {

Input::Input(std::vector<int> shape) : shape_(std::move(shape)) {}

void Input::accept(FlowVisitor& visitor) { visitor.visit(*this); }
std::string Input::op_type() const { return "Input"; }
std::vector<int> Input::shape() const { return shape_; }

}  // namespace janncy
