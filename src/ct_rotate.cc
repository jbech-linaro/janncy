#include "include/ct_rotate.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

CtRotate::CtRotate() : CtOp("CtRotate"){};
int CtRotate::amt() const { return amt_; }
void CtRotate::visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
  visitor->visit(ct_graph, this);
}

}  // namespace janncy
