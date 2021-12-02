#ifndef CONVLAYER_HPP_
#define CONVLAYER_HPP_

#include "Tensor.hpp"

class ConvLayer {
public:
    ConvLayer(Tensor input_tensor, Tensor filter, int stride);
    Tensor output_tensor() const;

private:
    int stride_;
    Tensor input_tensor_;
    Tensor filter_;
    Tensor output_tensor_;
};

#endif  // CONVLAYER_HPP_
