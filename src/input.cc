#include "include/input.h"

#include <utility>
#include <vector>

#include "include/flow.h"
#include "include/flow_visitor.h"
#include "include/graph.h"

namespace janncy {

void Input::Accept(FlowVisitor& visitor) const { visitor.Visit(*this); }

}  // namespace janncy
