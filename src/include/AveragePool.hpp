#ifndef AVERAGEPOOL_HPP_
#define AVERAGEPOOL_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

#include <string>

class FlowVisitor;

class AveragePool : public FlowNode {
  public:
    static AveragePool* create(FlowNode* parent, Tensor pool, int stride,
                               int padding) {
        return new AveragePool(parent, pool, stride, padding);
    }
    void visit(FlowVisitor* visitor);
    int stride() const;
    int padding() const;
    Tensor pool() const;
    std::string type_str() const { return "AveragePool"; }

  private:
    AveragePool(FlowNode* parent, Tensor pool, int stride, int padding);
    Tensor pool_;
    int stride_;
    int padding_;
};

#endif  // AVERAGEPOOL_HPP_
