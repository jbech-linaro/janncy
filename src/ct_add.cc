#include "include/ct_add.h"

#include "include/ct_graph_visitor.h"

namespace janncy {

CtAdd::CtAdd() : CtOp("CtAdd"){};

void CtAdd::Visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
  return visitor->Visit(ct_graph, this);
}

}  // namespace janncy
