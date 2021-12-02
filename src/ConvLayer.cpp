#include "include/ConvLayer.hpp"

#include "include/Tensor.hpp"

ConvLayer::ConvLayer(Tensor input_tensor, Tensor filter)
    : input_tensor_(input_tensor),
    filter_(filter),
    output_tensor_(Tensor({filter.shape()[0],
                input_tensor.shape()[1] - 2*(filter.shape()[2]/2),
                input_tensor.shape()[2] - 2*(filter.shape()[3]/2)})) {
}

Tensor ConvLayer::output_tensor() const {
    return output_tensor_;
}
