#include "include/flatten_layer.h"

#include "include/layer.h"
#include "include/layer_visitor.h"
#include "include/neural_network.h"

namespace janncy {

FlattenLayer::FlattenLayer(const Shape& input_shape)
    : output_dim_(input_shape.ValueCnt()) {}

void FlattenLayer::Accept(LayerVisitor& visitor) const { visitor.Visit(*this); }
std::string FlattenLayer::op_type() const { return "Flatten"; }
Shape FlattenLayer::shape() const { return {output_dim_}; }

}  // namespace janncy
