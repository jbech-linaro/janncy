#ifndef JANNCY_AVERAGE_POOL_H_
#define JANNCY_AVERAGE_POOL_H_

#include <string>
#include <vector>

#include "include/flow_node.h"
#include "include/kernel_attributes.h"

namespace janncy {

class FlowVisitor;

class AveragePool : public FlowNode {
 public:
  AveragePool(std::vector<int> input_shape, KernelAttributes kernel);

  void Accept(FlowVisitor& visitor) const override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

  const KernelAttributes& kernel() const;

 private:
  KernelAttributes kernel_;
  std::vector<int> output_shape_;
};

}  // namespace janncy

#endif  // JANNCY_AVERAGE_POOL_H_
