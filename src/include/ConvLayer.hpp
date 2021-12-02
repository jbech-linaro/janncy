#ifndef CONVLAYER_HPP_
#define CONVLAYER_HPP_

#include "Tensor.hpp"
#include "FlowNode.hpp"

class ConvLayer : public FlowNode {
public:
    ConvLayer(Tensor input_tensor, Tensor filter, int stride);
    Tensor output_tensor() const;
    Tensor input_tensor() const;
    int stride() const;

private:
    int stride_;
    Tensor filter_;
};

#endif  // CONVLAYER_HPP_
