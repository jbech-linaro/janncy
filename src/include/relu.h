#ifndef JANNCY_RELU_H_
#define JANNCY_RELU_H_

#include <string>
#include <vector>

#include "include/flow_node.h"

namespace janncy {

class FlowVisitor;

class ReLU : public FlowNode {
 public:
  ReLU(std::vector<int> shape);

  void Accept(FlowVisitor& visitor) const override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

 private:
  std::vector<int> shape_;
};

}  // namespace janncy

#endif  // JANNCY_RELU_H_
