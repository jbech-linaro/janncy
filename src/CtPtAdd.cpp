#include "include/CtPtAdd.hpp"

#include "include/CtGraph.hpp"
#include "include/CtGraphVisitor.hpp"

namespace janncy {

CtPtAdd::CtPtAdd() : CtOp("CtPtAdd"){};

std::vector<double> CtPtAdd::value() const { return value_; }

void CtPtAdd::visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
    return visitor->visit(ct_graph, this);
}

}  // namespace janncy
