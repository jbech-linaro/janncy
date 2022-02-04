#ifndef JANNCY_FHE_CONV_LAYER_H_
#define JANNCY_FHE_CONV_LAYER_H_

#include "include/fhe_layer.h"
#include "include/tensor_layout.h"

namespace janncy {

class ConvLayer;

class FheConvLayer : public FheLayer {
 public:
  explicit FheConvLayer(const ConvLayer* conv_layer, TensorLayout input_layout)
      : conv_layer_(conv_layer), input_layout_(input_layout) {
    (void)conv_layer_;
  }

  const TensorLayout& OutputLayout() const override;

  CtTensor MakeCtDag(CtDag& dag,
                     const std::vector<CtTensor>& ct_tensor) const override;

 private:
  const ConvLayer* conv_layer_;
  TensorLayout input_layout_;
};

}  // namespace janncy

#endif  // JANNCY_FHE_CONV_LAYER_H_
