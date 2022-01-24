#include "include/flatten.h"

#include "include/layer.h"
#include "include/layer_visitor.h"
#include "include/neural_network.h"

namespace janncy {

Flatten::Flatten(const Shape& input_shape)
    : output_dim_(input_shape.ValueCnt()) {}

void Flatten::Accept(LayerVisitor& visitor) const { visitor.Visit(*this); }
std::string Flatten::op_type() const { return "Flatten"; }
Shape Flatten::shape() const { return {output_dim_}; }

}  // namespace janncy
