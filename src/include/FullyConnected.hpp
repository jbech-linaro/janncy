#ifndef FULLYCONNECTED_HPP_
#define FULLYCONNECTED_HPP_

#include "FlowNode.hpp"

namespace janncy {

class FlowVisitor;
class Flow;

class FullyConnected : public FlowNode {
  public:
    FullyConnected(std::vector<int> output_shape);

    void visit(Flow* flow, FlowVisitor* visitor);
};

}  // namespace janncy

#endif  // FULLYCONNECTRED_HPP_
