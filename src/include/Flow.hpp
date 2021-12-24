#ifndef FLOW_HPP_
#define FLOW_HPP_

#include "Graph.hpp"

#include <vector>

class CtGraph;
class FlowNode;

class Flow : public Graph<FlowNode> {
  public:
    CtGraph* cipherfy();
};

#endif  // FLOWNODE_HPP_
