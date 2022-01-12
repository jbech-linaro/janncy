#include "include/CtPtMul.hpp"

#include "include/CtGraph.hpp"
#include "include/CtGraphVisitor.hpp"

namespace janncy {

CtPtMul::CtPtMul() : CtOp("CtPtMul"){};

std::vector<double> CtPtMul::value() const { return value_; }

void CtPtMul::visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
    return visitor->visit(ct_graph, this);
}

}  // namespace janncy
