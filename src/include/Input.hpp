#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "FlowNode.hpp"

#include <vector>

class Flow;
class FlowVisitor;

class Input : public FlowNode {
  public:
    Input(std::vector<int> input_tensor);

    void visit(Flow* flow, FlowVisitor* visitor);
};

#endif  // INPUT_HPP_
