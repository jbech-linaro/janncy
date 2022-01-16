#include "include/ct_input.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

CtInput::CtInput() : CtOp("CtInput"){};

void CtInput::Visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
  return visitor->Visit(ct_graph, this);
}

}  // namespace janncy
