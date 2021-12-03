#include "include/ConvLayer.hpp"

#include "include/FlowNode.hpp"
#include "include/Tensor.hpp"

ConvLayer::ConvLayer(FlowNode* parent, Tensor filter, int stride)
    : FlowNode(parent, Tensor({filter.shape()[0],
                (parent->output_tensor().shape()[1] - 2*(filter.shape()[2]/2)) / stride,
                (parent->output_tensor().shape()[2] - 2*(filter.shape()[3]/2)) / stride})),
    stride_(stride),
    filter_(filter) {
}

int ConvLayer::stride() const {
    return stride_;
}

Tensor ConvLayer::output_tensor() const {
    return output_tensor_;
}
