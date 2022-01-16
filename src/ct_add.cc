#include "include/ct_add.h"

#include "include/ct_graph_visitor.h"

namespace janncy {

CtAdd::CtAdd() : CtOp("CtAdd"){};
void CtAdd::visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
  return visitor->visit(ct_graph, this);
}

}  // namespace janncy
