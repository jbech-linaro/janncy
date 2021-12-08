#ifndef FLOW_HPP_
#define FLOW_HPP_

#include "CtGraph.hpp"
#include "Graph.hpp"

#include <vector>

class FlowNode;
class Input;

class Flow : public Graph<FlowNode> {
  public:
    Input* input(Tensor input_tensor);
    CtGraph cipherfy();
};

#endif  // FLOWNODE_HPP_
