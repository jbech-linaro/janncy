#include "include/CtMul.hpp"

#include "include/CtGraph.hpp"
#include "include/CtGraphVisitor.hpp"

namespace janncy {

CtMul::CtMul() : CtOp("CtMul"){};
void CtMul::visit(CtGraph* ct_graph, CtGraphVisitor* visitor) {
    return visitor->visit(ct_graph, this);
}

}  // namespace janncy
