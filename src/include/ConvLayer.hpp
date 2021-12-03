#ifndef CONVLAYER_HPP_
#define CONVLAYER_HPP_

#include "Tensor.hpp"
#include "FlowNode.hpp"

class ConvLayer : public FlowNode {
public:
    ConvLayer(FlowNode* parent, Tensor filter, int stride);
    Tensor output_tensor() const;
    Tensor input_tensor() const;
    int stride() const;
    std::string type_str() const { return "ConvLayer"; }

private:
    int stride_;
    Tensor filter_;
};

#endif  // CONVLAYER_HPP_
