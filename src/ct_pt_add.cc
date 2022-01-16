#include "include/ct_pt_add.h"

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

CtPtAdd::CtPtAdd() : CtOp("CtPtAdd"){};

std::vector<double> CtPtAdd::value() const { return value_; }

void CtPtAdd::Visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
  return visitor->Visit(ct_graph, this);
}

}  // namespace janncy
