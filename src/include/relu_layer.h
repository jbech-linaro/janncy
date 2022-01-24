#ifndef JANNCY_RELU_LAYER_H_
#define JANNCY_RELU_LAYER_H_

#include <string>
#include <vector>

#include "include/layer.h"
#include "include/shape.h"

namespace janncy {

class LayerVisitor;

class ReluLayer : public Layer {
 public:
  ReluLayer(Shape shape);

  void Accept(LayerVisitor& visitor) const override;
  std::string op_type() const override;
  Shape shape() const override;

 private:
  Shape shape_;
};

}  // namespace janncy

#endif  // JANNCY_RELU_LAYER_H_
