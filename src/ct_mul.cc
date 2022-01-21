#include "include/ct_mul.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

void CtMul::Accept(CtGraphVisitor& visitor) { return visitor.Visit(*this); }
std::string CtMul::op_type() const { return "CtMul"; }

}  // namespace janncy
