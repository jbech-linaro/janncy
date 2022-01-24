#include "include/fully_connected_layer.h"

#include <string>
#include <vector>

#include "include/layer_visitor.h"

namespace janncy {

FullyConnectedLayer::FullyConnectedLayer(int input_size, int output_size)
    : input_size_(input_size), output_size_(output_size) {}

void FullyConnectedLayer::Accept(LayerVisitor& visitor) const {
  visitor.Visit(*this);
}
std::string FullyConnectedLayer::op_type() const { return "FullyConnected"; }
Shape FullyConnectedLayer::shape() const { return {output_size()}; }

int FullyConnectedLayer::input_size() const { return input_size_; }
int FullyConnectedLayer::output_size() const { return output_size_; }

}  // namespace janncy
