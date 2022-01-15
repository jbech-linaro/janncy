#include "include/Flatten.hpp"

#include "include/Flow.hpp"
#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"

namespace janncy {

Flatten::Flatten(const std::vector<int> &input_shape) {
  output_dim_ = 1;
  for (int d : input_shape) {
    output_dim_ *= d;
  }
}

void Flatten::accept(FlowVisitor &visitor) { visitor.visit(*this); }
std::string Flatten::op_type() const { return "Flatten"; }
std::vector<int> Flatten::shape() const { return {output_dim_}; }

}  // namespace janncy
