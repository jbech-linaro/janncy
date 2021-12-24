#ifndef MAXPOOL_HPP_
#define MAXPOOL_HPP_

#include "FlowNode.hpp"

#include <string>
#include <vector>

class FlowVisitor;
class Flow;

class MaxPool : public FlowNode {
  public:
    MaxPool(std::vector<int> output_shape, std::vector<int> kernel_shape,
            std::vector<int> stride, std::vector<int> padding);

    void visit(Flow* flow, FlowVisitor* visitor);

    std::vector<int> stride() const;
    std::vector<int> padding() const;
    std::vector<int> kernel_shape() const;

  private:
    std::vector<int> kernel_shape_;
    std::vector<int> stride_;
    std::vector<int> padding_;
};

#endif  // MAXPOOL_HPP_
