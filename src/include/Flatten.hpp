#ifndef FLATTEN_HPP_
#define FLATTEN_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class FlowVisitor;

class Flatten : public FlowNode {
  public:
    static Flatten* create(FlowNode* parent, int axis) {
        return new Flatten(parent, axis);
    }
    void visit(FlowVisitor* visitor);
    std::string type_str() const { return "Flatten"; }

  private:
    Flatten(FlowNode* parent, int axis);
};

#endif  // FLATTEN_HPP_
