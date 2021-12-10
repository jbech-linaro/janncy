#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class Flow;
template <class T> class Graph;
class FlowVisitor;

class Input : public FlowNode {
  public:
    static Input* create(Graph<FlowNode>* flow, Tensor input_tensor) {
        return new Input(flow, input_tensor);
    }
    void visit(FlowVisitor* visitor);
    std::string type_str() const { return "Input"; }

  private:
    Input(Graph<FlowNode>* flow, Tensor input_tensor);
};

#endif  // INPUT_HPP_
