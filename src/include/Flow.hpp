#ifndef FLOW_HPP_
#define FLOW_HPP_

#include "Graph.hpp"
#include "Tensor.hpp"

#include <vector>

class CtGraph;
class FlowNode;
class Input;

class Flow : public Graph<FlowNode> {
  public:
    Input* input(Tensor input_tensor);
    CtGraph* cipherfy();
};

#endif  // FLOWNODE_HPP_
