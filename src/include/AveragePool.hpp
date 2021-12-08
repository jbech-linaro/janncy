#ifndef AVERAGEPOOL_HPP_
#define AVERAGEPOOL_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class AveragePool : public FlowNode {
  public:
    static AveragePool* create(FlowNode* parent, Tensor pool, int stride,
                               bool padded) {
        return new AveragePool(FlowNode * parent, Tensor pool, int stride,
                               bool padded);
    }
    int stride() const;
    bool padded() const;
    std::string type_str() const { return "AveragePool"; }
    CtTensor cipherfy(std::vector<CtTensor> parents) const;

  private:
    AveragePool(FlowNode* parent, Tensor pool, int stride, bool padded);
    Tensor pool_;
    int stride_;
    bool padded_;
};

#endif  // AVERAGEPOOL_HPP_
