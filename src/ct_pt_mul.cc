#include "include/ct_pt_mul.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

CtPtMul::CtPtMul() : CtOp("CtPtMul"){};

std::vector<double> CtPtMul::value() const { return value_; }

void CtPtMul::Accept(CtGraphVisitor& visitor) { return visitor.Visit(*this); }

}  // namespace janncy
