#ifndef JANNCY_INPUT_LAYER_H_
#define JANNCY_INPUT_LAYER_H_

#include <vector>

#include "include/layer.h"

namespace janncy {

class LayerVisitor;

class InputLayer : public Layer {
 public:
  InputLayer(Shape shape) : shape_(std::move(shape)){};

  void Accept(LayerVisitor& visitor) const override;
  std::string op_type() const override { return "InputLayer"; };
  Shape shape() const override { return shape_; }

 private:
  Shape shape_;
};

}  // namespace janncy

#endif  // JANNCY_INPUT_LAYER_H_
