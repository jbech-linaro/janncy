#ifndef FLOW_HPP_
#define FLOW_HPP_

#include "Graph.hpp"

#include <vector>

namespace janncy {

class CtGraph;
class FlowNode;

class Flow : public Graph<FlowNode> {
  public:
    CtGraph* cipherfy();
};

}  // namespace janncy

#endif  // FLOWNODE_HPP_
