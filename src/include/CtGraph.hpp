#ifndef CTGRAPH_HPP_
#define CTGRAPH_HPP_

#include "Graph.hpp"

class CtOp;

class CtGraph : public Graph {
public:
    CtOp* input();

    CtOp* add_pt(CtOp* parent);
    CtOp* mul_pt(CtOp* parent);
    CtOp* add(CtOp* parent0, CtOp* parent1);
    CtOp* mul(CtOp* parent0, CtOp* parent1);
    CtOp* rotate(CtOp* parent0);
};

#endif  // CTGRAPH_HPP_
