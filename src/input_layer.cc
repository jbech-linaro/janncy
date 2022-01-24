#include "include/input_layer.h"

#include <utility>
#include <vector>

#include "include/layer_visitor.h"
#include "include/neural_network.h"

namespace janncy {

void InputLayer::Accept(LayerVisitor& visitor) const { visitor.Visit(*this); }

}  // namespace janncy
