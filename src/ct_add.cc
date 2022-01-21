#include "include/ct_add.h"

#include <string>

#include "include/ct_graph_visitor.h"

namespace janncy {

void CtAdd::Accept(CtGraphVisitor& visitor) { return visitor.Visit(*this); }
std::string CtAdd::op_type() const { return "CtAdd"; }

}  // namespace janncy
