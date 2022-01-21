#include "include/ct_pt_add.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

std::string CtPtAdd::op_type() const { return "CtPtAdd"; }
void CtPtAdd::Accept(CtGraphVisitor& visitor) { return visitor.Visit(*this); }

std::vector<double> CtPtAdd::value() const { return value_; }
}  // namespace janncy
