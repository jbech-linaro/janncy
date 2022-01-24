#ifndef JANNCY_BATCH_NORMALIZATION_H_
#define JANNCY_BATCH_NORMALIZATION_H_

#include <string>
#include <vector>

#include "include/layer.h"
#include "include/shape.h"

class FlowVisitor;

namespace janncy {

class BatchNormalization : public Layer {
 public:
  BatchNormalization(Shape shape);

  void Accept(FlowVisitor& visitor) const override;
  std::string op_type() const override;
  Shape shape() const override;

 private:
  Shape shape_;
};

}  // namespace janncy

#endif  // JANNCY_BATCH_NORMALIZATION_H_
