#ifndef MAXPOOL_HPP_
#define MAXPOOL_HPP_

#include <string>
#include <vector>

#include "FlowNode.hpp"
#include "KernelAttributes.hpp"

namespace janncy {

class FlowVisitor;

class MaxPool : public FlowNode {
 public:
  MaxPool(std::vector<int> input_shape, KernelAttributes kernel);

  void accept(FlowVisitor& visitor) override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

 private:
  KernelAttributes kernel_;
  std::vector<int> output_shape_;
};

}  // namespace janncy

#endif  // MAXPOOL_HPP_
