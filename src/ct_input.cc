#include "include/ct_input.h"

#include "include/ct_dag.h"
#include "include/ct_op_visitor.h"

namespace janncy {

void CtInput::Accept(CtOpVisitor& visitor) const {
  return visitor.Visit(*this);
}
std::string CtInput::op_type() const { return "CtInput"; }

}  // namespace janncy
