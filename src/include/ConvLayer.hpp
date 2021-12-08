#ifndef CONVLAYER_HPP_
#define CONVLAYER_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class ConvLayer : public FlowNode {
  public:
    static ConvLayer* create(FlowNode* parent, Tensor filter, int stride,
                             bool padded) {
        return new ConvLayer(parent, filter, stride, padded);
    };
    Tensor output_tensor() const;
    Tensor input_tensor() const;
    int stride() const;
    bool padded() const;
    std::string type_str() const { return "ConvLayer"; }
    CtTensor cipherfy(std::vector<CtTensor> parents) const;

  private:
    ConvLayer(FlowNode* parent, Tensor filter, int stride, bool padded);
    int stride_;
    Tensor filter_;
    bool padded_;
};

#endif  // CONVLAYER_HPP_
