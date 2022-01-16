#include "include/ct_mul.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

CtMul::CtMul() : CtOp("CtMul"){};

void CtMul::Accept(CtGraphVisitor& visitor) { return visitor.Visit(this); }

}  // namespace janncy
