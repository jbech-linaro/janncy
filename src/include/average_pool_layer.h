#ifndef JANNCY_AVERAGE_POOL_LAYER_H_
#define JANNCY_AVERAGE_POOL_LAYER_H_

#include <string>
#include <vector>

#include "include/kernel_attributes.h"
#include "include/layer.h"
#include "include/shape.h"

namespace janncy {

class LayerVisitor;

class AveragePoolLayer : public Layer {
 public:
  AveragePoolLayer(Shape input_shape, KernelAttributes kernel);

  void Accept(LayerVisitor& visitor) const override;
  std::string op_type() const override;
  Shape shape() const override;

  const KernelAttributes& kernel() const;

 private:
  KernelAttributes kernel_;
  Shape output_shape_;
};

}  // namespace janncy

#endif  // JANNCY_AVERAGE_POOL_LAYER_H_
