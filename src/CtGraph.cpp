#include "include/CtGraph.hpp"

#include "include/CtOp.hpp"
#include "include/CtAdd.hpp"
#include "include/CtMul.hpp"
#include "include/CtRotate.hpp"
#include "include/CtInput.hpp"

CtOp* CtGraph::input() {
    auto in_node = new CtInput();
    add_node(in_node);
    return in_node;
}

CtOp* CtGraph::add(CtOp* parent0, CtOp* parent1) {
    auto add_n = new CtAdd(parent0, parent1);
    parent0->add_child(add_n);
    parent1->add_child(add_n);
    add_node(add_n);
    return add_n;
}

CtOp* CtGraph::mul(CtOp* parent0, CtOp* parent1) {
   auto mul_node = new CtMul(parent0, parent1);
   parent0->add_child(mul_node);
   parent1->add_child(mul_node);
   add_node(mul_node);
    return mul_node;
}

CtOp* CtGraph::rotate(CtOp* parent) {
   auto rotate_node = new CtRotate(parent);
   parent->add_child(rotate_node);
   add_node(rotate_node);
   return rotate_node;
}
