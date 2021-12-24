#include "include/CtMul.hpp"

#include "include/CtGraph.hpp"
#include "include/CtGraphVisitor.hpp"

CtMul::CtMul() : CtOp("CtMul"){};
void CtMul::visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
    return visitor->visit(ct_graph, this);
}
