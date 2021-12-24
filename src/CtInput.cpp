#include "include/CtInput.hpp"

#include "include/CtGraph.hpp"
#include "include/CtGraphVisitor.hpp"

CtInput::CtInput() : CtOp("CtInput"){};

void CtInput::visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
    return visitor->visit(ct_graph, this);
}
