#ifndef CONVLAYER_HPP_
#define CONVLAYER_HPP_

#include "Tensor.hpp"

class ConvLayer {
public:
    ConvLayer(Tensor input_tensor, Tensor filter);
    Tensor output_tensor() const;

private:
    Tensor input_tensor_;
    Tensor filter_;
    Tensor output_tensor_;
};

#endif  // CONVLAYER_HPP_
