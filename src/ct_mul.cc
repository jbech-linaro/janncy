#include "include/ct_mul.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

CtMul::CtMul() : CtOp("CtMul"){};
void CtMul::Visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
  return visitor->Visit(ct_graph, this);
}

}  // namespace janncy
