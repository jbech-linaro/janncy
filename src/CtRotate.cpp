#include "include/CtRotate.hpp"

#include "include/CtGraph.hpp"
#include "include/CtGraphVisitor.hpp"

CtRotate::CtRotate() : CtOp("CtRotate"){};
int CtRotate::amt() const { return amt_; }
void CtRotate::visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
    visitor->visit(ct_graph, this);
}
