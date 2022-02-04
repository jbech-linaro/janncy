#ifndef JANNCY_FHE_LAYER_H_
#define JANNCY_FHE_LAYER_H_

#include "include/ct_dag.h"
#include "include/ct_tensor.h"
#include "include/tensor_layout.h"

namespace janncy {

class FheLayer {
 public:
  FheLayer() = default;
  FheLayer(FheLayer&&) = default;
  virtual ~FheLayer() {}
  FheLayer(const FheLayer&) = delete;
  FheLayer& operator=(const FheLayer&) = delete;
  FheLayer& operator=(const FheLayer&&) = delete;

  virtual const TensorLayout& OutputLayout() const = 0;

  virtual CtTensor MakeCtDag(CtDag& dag,
                             const std::vector<CtTensor>& ct_tensor) const = 0;
};

}  // namespace janncy

#endif  // JANNCY_FHE_LAYER_H_
