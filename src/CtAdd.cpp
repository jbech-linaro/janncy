#include "include/CtAdd.hpp"

#include "include/CtGraphVisitor.hpp"

namespace janncy {

CtAdd::CtAdd() : CtOp("CtAdd"){};
void CtAdd::visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
  return visitor->visit(ct_graph, this);
}

}  // namespace janncy
