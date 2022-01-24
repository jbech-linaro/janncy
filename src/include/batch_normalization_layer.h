#ifndef JANNCY_BATCH_NORMALIZATION_LAYER_H_
#define JANNCY_BATCH_NORMALIZATION_LAYER_H_

#include <string>
#include <vector>

#include "include/layer.h"
#include "include/shape.h"

class LayerVisitor;

namespace janncy {

class BatchNormalizationLayer : public Layer {
 public:
  BatchNormalizationLayer(Shape shape);

  void Accept(LayerVisitor& visitor) const override;
  std::string op_type() const override;
  Shape shape() const override;

 private:
  Shape shape_;
};

}  // namespace janncy

#endif  // JANNCY_BATCH_NORMALIZATION_LAYER_H_
