#ifndef ADD_HPP_
#define ADD_HPP_

#include "FlowNode.hpp"

class FlowVisitor;

class Add : public FlowNode {
  public:
    std::string type_str() const { return "Add"; }
    void visit(FlowVisitor* visitor);
    static Add* create(FlowNode* parent0, FlowNode* parent1) {
        return new Add(parent0, parent1);
    }

  private:
    Add(FlowNode* parent0, FlowNode* parent1);
};

#endif  // ADD_HPP_
