#ifndef RELU_HPP_
#define RELU_HPP_

#include "FlowNode.hpp"

namespace janncy {

class FlowVisitor;
class Flow;

class ReLU : public FlowNode {
  public:
    ReLU(std::vector<int> output_shape);

    void visit(Flow* flow, FlowVisitor* visitor);
};

}  // namespace janncy

#endif  // RELU_HPP_
