#ifndef JANNCY_CONV_LAYER_H_
#define JANNCY_CONV_LAYER_H_

#include <vector>

#include "include/flow_node.h"
#include "include/kernel_attributes.h"

namespace janncy {

class FlowVisitor;

class ConvLayer : public FlowNode {
 public:
  ConvLayer(std::vector<int> input_shape, KernelAttributes kernel,
            int output_ch);

  void Accept(FlowVisitor& visitor) const override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

  const KernelAttributes& kernel() const;

 private:
  KernelAttributes kernel_;
  std::vector<int> output_shape_;
};

}  // namespace janncy

#endif  // JANNCY_CONV_LAYER_H_
