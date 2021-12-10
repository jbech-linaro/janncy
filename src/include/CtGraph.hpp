#ifndef CTGRAPH_HPP_
#define CTGRAPH_HPP_

#include "CtOp.hpp"
#include "Graph.hpp"

class CtGraph : public Graph<CtOp> {
  public:
    CtGraph(){};
};

#endif  // CTGRAPH_HPP_
