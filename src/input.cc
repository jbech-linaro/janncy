#include "include/input.h"

#include <utility>
#include <vector>

#include "include/flow_visitor.h"
#include "include/neural_network.h"

namespace janncy {

void Input::Accept(FlowVisitor& visitor) const { visitor.Visit(*this); }

}  // namespace janncy
