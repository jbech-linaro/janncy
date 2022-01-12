#ifndef FLOWNODE_HPP_
#define FLOWNODE_HPP_

#include "CtTensor.hpp"
#include "Panic.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace janncy {

class Flow;
class FlowVisitor;

class FlowNode {
  public:
    FlowNode(std::vector<int> output_shape, std::string op_type);

    const std::vector<int>& shape() const;

    FlowNode(const FlowNode&) = delete;
    FlowNode& operator=(const FlowNode&) = delete;
    FlowNode(FlowNode&&) = delete;
    FlowNode& operator=(FlowNode&&) = delete;

    virtual void visit(Flow* flow, FlowVisitor* visitor) = 0;

    std::string str() const;
    std::string op_type() const;

  private:
    std::vector<int> output_shape_;
    std::string op_type_;
};

}  // namespace janncy

#endif  // FLOWNODE_HPP_
