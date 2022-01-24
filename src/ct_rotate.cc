#include "include/ct_rotate.h"

#include "include/ct_dag.h"
#include "include/ct_op_visitor.h"

namespace janncy {

void CtRotate::Accept(CtOpVisitor& visitor) const { visitor.Visit(*this); }
std::string CtRotate::op_type() const { return "CtRotate"; }

int CtRotate::amt() const { return amt_; }
}  // namespace janncy
