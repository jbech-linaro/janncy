#include "include/flatten.h"

#include "include/flow.h"
#include "include/flow_node.h"
#include "include/flow_visitor.h"

namespace janncy {

Flatten::Flatten(const Shape& input_shape)
    : output_dim_(input_shape.ValueCnt()) {}

void Flatten::Accept(FlowVisitor& visitor) const { visitor.Visit(*this); }
std::string Flatten::op_type() const { return "Flatten"; }
Shape Flatten::shape() const { return {output_dim_}; }

}  // namespace janncy
