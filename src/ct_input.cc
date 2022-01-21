#include "include/ct_input.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

void CtInput::Accept(CtGraphVisitor& visitor) const {
  return visitor.Visit(*this);
}
std::string CtInput::op_type() const { return "CtInput"; }

}  // namespace janncy
