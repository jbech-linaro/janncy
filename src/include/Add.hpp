#ifndef ADD_HPP_
#define ADD_HPP_

#include "FlowNode.hpp"

class FlowVisitor;
class Flow;

class Add : public FlowNode {
  public:
    Add(std::vector<int> output_shape);
    void visit(Flow* flow, FlowVisitor* visitor);
};

#endif  // ADD_HPP_
