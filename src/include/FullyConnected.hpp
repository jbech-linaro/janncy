#ifndef FULLYCONNECTED_HPP_
#define FULLYCONNECTED_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class FlowVisitor;

class FullyConnected : public FlowNode {
  public:
    static FullyConnected* create(FlowNode* parent, Tensor matrix) {
        return new FullyConnected(parent, matrix);
    }
    void visit(FlowVisitor* visitor);
    std::string type_str() const { return "FullyConnected"; }

  private:
    FullyConnected(FlowNode* parent, Tensor matrix);
};

#endif  // FULLYCONNECTRED_HPP_
