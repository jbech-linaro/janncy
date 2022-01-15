#ifndef RELU_HPP_
#define RELU_HPP_

#include <vector>

#include "FlowNode.hpp"

namespace janncy {

class FlowVisitor;

class ReLU : public FlowNode {
 public:
  ReLU(std::vector<int> shape);

  void accept(FlowVisitor& visitor) override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

 private:
  std::vector<int> shape_;
};

}  // namespace janncy

#endif  // RELU_HPP_
