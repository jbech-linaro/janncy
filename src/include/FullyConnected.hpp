#ifndef FULLYCONNECTED_HPP_
#define FULLYCONNECTED_HPP_

#include "FlowNode.hpp"

class FlowVisitor;
class Flow;

class FullyConnected : public FlowNode {
  public:
    FullyConnected(std::vector<int> output_shape);

    void visit(Flow* flow, FlowVisitor* visitor);
};

#endif  // FULLYCONNECTRED_HPP_
