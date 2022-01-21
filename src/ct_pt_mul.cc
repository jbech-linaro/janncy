#include "include/ct_pt_mul.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

void CtPtMul::Accept(CtGraphVisitor& visitor) { return visitor.Visit(*this); }
std::string CtPtMul::op_type() const { return "CtPtMul"; }

std::vector<double> CtPtMul::value() const { return value_; }

}  // namespace janncy
