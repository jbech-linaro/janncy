#include "include/CtAdd.hpp"

#include "include/CtGraphVisitor.hpp"

CtAdd::CtAdd() : CtOp("CtAdd"){};
void CtAdd::visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
    return visitor->visit(ct_graph, this);
}
