#ifndef CTGRAPH_HPP_
#define CTGRAPH_HPP_

#include "Graph.hpp"

class CtInput;

class CtGraph : public Graph<CtOp> {
  public:
    CtInput* input();
};

#endif  // CTGRAPH_HPP_
