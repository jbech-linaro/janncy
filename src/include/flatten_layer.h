#ifndef JANNCY_FLATTEN_LAYER_H_
#define JANNCY_FLATTEN_LAYER_H_

#include <string>
#include <vector>

#include "include/layer.h"
#include "include/shape.h"

namespace janncy {

class LayerVisitor;

class FlattenLayer : public Layer {
 public:
  FlattenLayer(const Shape& input_shape);

  void Accept(LayerVisitor& visitor) const override;
  std::string op_type() const override;
  Shape shape() const override;

 private:
  int output_dim_;
};

}  // namespace janncy

#endif  // JANNCY_FLATTEN_LAYER_H_
