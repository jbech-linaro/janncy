#include "include/ct_input.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

CtInput::CtInput() : CtOp("CtInput"){};

void CtInput::Accept(CtGraphVisitor& visitor) { return visitor.Visit(*this); }

}  // namespace janncy
