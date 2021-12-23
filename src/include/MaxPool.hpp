#ifndef MAXPOOL_HPP_
#define MAXPOOL_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

#include <string>

class FlowVisitor;

class MaxPool : public FlowNode {
  public:
    static MaxPool* create(FlowNode* parent, Tensor pool, int stride,
                           bool padding) {
        return new MaxPool(parent, pool, stride, padding);
    }
    void visit(FlowVisitor* visitor);
    int stride() const;
    int padding() const;
    Tensor pool() const;
    std::string type_str() const { return "MaxPool"; }

  private:
    MaxPool(FlowNode* parent, Tensor pool, int stride, bool padding);
    Tensor pool_;
    int stride_;
    int padding_;
};

#endif  // MAXPOOL_HPP_
