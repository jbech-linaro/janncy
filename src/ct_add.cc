#include "include/ct_add.h"

#include <string>

#include "include/ct_op_visitor.h"

namespace janncy {

void CtAdd::Accept(CtOpVisitor& visitor) const { return visitor.Visit(*this); }
std::string CtAdd::op_type() const { return "CtAdd"; }

}  // namespace janncy
