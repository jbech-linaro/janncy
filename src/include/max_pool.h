#ifndef JANNCY_MAX_POOL_H_
#define JANNCY_MAX_POOL_H_

#include <string>
#include <vector>

#include "include/kernel_attributes.h"
#include "include/layer.h"
#include "include/shape.h"

namespace janncy {

class FlowVisitor;

class MaxPool : public Layer {
 public:
  MaxPool(Shape input_shape, KernelAttributes kernel);

  void Accept(FlowVisitor& visitor) const override;
  std::string op_type() const override;
  Shape shape() const override;

 private:
  KernelAttributes kernel_;
  Shape output_shape_;
};

}  // namespace janncy

#endif  // JANNCY_MAX_POOL_H_
