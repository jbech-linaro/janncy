#ifndef JANNCY_MAX_POOL_H_
#define JANNCY_MAX_POOL_H_

#include <string>
#include <vector>

#include "include/flow_node.h"
#include "include/kernel_attributes.h"

namespace janncy {

class FlowVisitor;

class MaxPool : public FlowNode {
 public:
  MaxPool(std::vector<int> input_shape, KernelAttributes kernel);

  void Accept(FlowVisitor& visitor) override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

 private:
  KernelAttributes kernel_;
  std::vector<int> output_shape_;
};

}  // namespace janncy

#endif  // JANNCY_MAX_POOL_H_
