#ifndef AVERAGEPOOL_HPP_
#define AVERAGEPOOL_HPP_

#include <vector>

#include "FlowNode.hpp"
#include "KernelAttributes.hpp"

namespace janncy {

class FlowVisitor;

class AveragePool : public FlowNode {
 public:
  AveragePool(std::vector<int> input_shape, KernelAttributes kernel);

  void accept(FlowVisitor& visitor) override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

  const KernelAttributes& kernel() const;

 private:
  KernelAttributes kernel_;
  std::vector<int> output_shape_;
};

}  // namespace janncy

#endif  // AVERAGEPOOL_HPP_
