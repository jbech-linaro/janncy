#include "include/flatten.h"

#include "include/flow.h"
#include "include/flow_node.h"
#include "include/flow_visitor.h"

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
