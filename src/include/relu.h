#ifndef JANNCY_RELU_H_
#define JANNCY_RELU_H_

#include <string>
#include <vector>

#include "include/flow_node.h"
#include "include/shape.h"

namespace janncy {

class FlowVisitor;

class ReLU : public FlowNode {
 public:
  ReLU(Shape shape);

  void Accept(FlowVisitor& visitor) const override;
  std::string op_type() const override;
  Shape shape() const override;

 private:
  Shape shape_;
};

}  // namespace janncy

#endif  // JANNCY_RELU_H_
