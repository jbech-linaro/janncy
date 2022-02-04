#include "include/fhe_conv_layer.h"

namespace janncy {

const TensorLayout& FheConvLayer::OutputLayout() const { return input_layout_; }

CtTensor FheConvLayer::MakeCtDag(CtDag& dag,
                                 const std::vector<CtTensor>& ct_tensor) const {
  return ct_tensor[0];
}

}  // namespace janncy
