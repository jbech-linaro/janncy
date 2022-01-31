#include "include/ct_pt_mul.h"

#include "include/ct_dag.h"
#include "include/ct_op_visitor.h"

namespace janncy {

void CtPtMul::Accept(CtOpVisitor& visitor) const {
  return visitor.Visit(*this);
}

std::string CtPtMul::op_type() const { return "CtPtMul"; }

}  // namespace janncy
