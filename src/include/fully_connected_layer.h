#ifndef JANNCY_FULLY_CONNECTED_LAYER_H_
#define JANNCY_FULLY_CONNECTED_LAYER_H_

#include "include/layer.h"
#include "include/shape.h"

namespace janncy {

class LayerVisitor;

class FullyConnectedLayer : public Layer {
 public:
  FullyConnectedLayer(int input_size, int output_size);

  void Accept(LayerVisitor& visitor) const override;
  std::string op_type() const override;
  Shape shape() const override;

  int input_size() const;
  int output_size() const;

 private:
  int input_size_;
  int output_size_;
};

}  // namespace janncy

#endif  // JANNCY_FULLY_CONNECTED_LAYER_H_
