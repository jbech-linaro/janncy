#include "include/ct_mul.h"

#include "include/ct_dag.h"
#include "include/ct_op_visitor.h"

namespace janncy {

void CtMul::Accept(CtOpVisitor& visitor) const { return visitor.Visit(*this); }
std::string CtMul::op_type() const { return "CtMul"; }

}  // namespace janncy
