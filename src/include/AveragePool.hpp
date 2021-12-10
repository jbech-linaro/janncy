#ifndef AVERAGEPOOL_HPP_
#define AVERAGEPOOL_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class FlowVisitor;

class AveragePool : public FlowNode {
  public:
    static AveragePool* create(FlowNode* parent, Tensor pool, int stride,
                               bool padded) {
        return new AveragePool(parent, pool, stride, padded);
    }
    void visit(FlowVisitor* visitor);
    int stride() const;
    bool padded() const;
    Tensor pool() const;
    std::string type_str() const { return "AveragePool"; }

  private:
    AveragePool(FlowNode* parent, Tensor pool, int stride, bool padded);
    Tensor pool_;
    int stride_;
    bool padded_;
};

#endif  // AVERAGEPOOL_HPP_
