#ifndef CTGRAPH_HPP_
#define CTGRAPH_HPP_

#include "CtOp.hpp"
#include "CtTensor.hpp"
#include "Graph.hpp"

class FlowNode;

class CtGraph : public Graph<CtOp> {
  public:
    CtTensor input(FlowNode* input_node);
};

#endif  // CTGRAPH_HPP_
