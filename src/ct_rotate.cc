#include "include/ct_rotate.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

CtRotate::CtRotate() : CtOp("CtRotate"){};
int CtRotate::amt() const { return amt_; }
void CtRotate::Visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
  visitor->Visit(ct_graph, this);
}

}  // namespace janncy
