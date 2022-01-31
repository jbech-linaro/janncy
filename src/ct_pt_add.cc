#include "include/ct_pt_add.h"

#include "include/ct_dag.h"
#include "include/ct_op_visitor.h"

namespace janncy {

void CtPtAdd::Accept(CtOpVisitor& visitor) const {
  return visitor.Visit(*this);
}

std::string CtPtAdd::op_type() const { return "CtPtAdd"; }

}  // namespace janncy
