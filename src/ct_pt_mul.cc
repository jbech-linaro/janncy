#include "include/ct_pt_mul.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

CtPtMul::CtPtMul() : CtOp("CtPtMul"){};

std::vector<double> CtPtMul::value() const { return value_; }

void CtPtMul::Visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
  return visitor->Visit(ct_graph, this);
}

}  // namespace janncy
