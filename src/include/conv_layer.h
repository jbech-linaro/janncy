#ifndef JANNCY_CONV_LAYER_H_
#define JANNCY_CONV_LAYER_H_

#include <vector>

#include "include/flow_node.h"
#include "include/kernel_attributes.h"
#include "include/shape.h"

namespace janncy {

class FlowVisitor;

class ConvLayer : public FlowNode {
 public:
  ConvLayer(Shape input_shape, KernelAttributes kernel, int output_ch);

  void Accept(FlowVisitor& visitor) const override;
  std::string op_type() const override;
  Shape shape() const override;

  const KernelAttributes& kernel() const;

 private:
  KernelAttributes kernel_;
  Shape output_shape_;
};

}  // namespace janncy

#endif  // JANNCY_CONV_LAYER_H_
