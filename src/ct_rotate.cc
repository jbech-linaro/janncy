#include "include/ct_rotate.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

void CtRotate::Accept(CtGraphVisitor& visitor) const { visitor.Visit(*this); }
std::string CtRotate::op_type() const { return "CtRotate"; }

int CtRotate::amt() const { return amt_; }
}  // namespace janncy
