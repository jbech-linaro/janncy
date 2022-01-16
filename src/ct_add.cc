#include "include/ct_add.h"

#include "include/ct_graph_visitor.h"

namespace janncy {

CtAdd::CtAdd() : CtOp("CtAdd"){};

void CtAdd::Accept(CtGraphVisitor& visitor) { return visitor.Visit(this); }

}  // namespace janncy
