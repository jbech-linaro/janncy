#ifndef JANNCY_INPUT_H_
#define JANNCY_INPUT_H_

#include <vector>

#include "include/flow_node.h"

namespace janncy {

class FlowVisitor;

class Input : public FlowNode {
 public:
  Input(Shape shape) : shape_(std::move(shape)){};

  void Accept(FlowVisitor& visitor) const override;
  std::string op_type() const override { return "InputLayer"; };
  Shape shape() const override { return shape_; }

 private:
  Shape shape_;
};

}  // namespace janncy

#endif  // JANNCY_INPUT_H_
