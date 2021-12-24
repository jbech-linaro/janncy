#ifndef RELU_HPP_
#define RELU_HPP_

#include "FlowNode.hpp"

class FlowVisitor;
class Flow;

class ReLU : public FlowNode {
  public:
    ReLU(std::vector<int> output_shape);

    void visit(Flow* flow, FlowVisitor* visitor);
};

#endif  // RELU_HPP_
