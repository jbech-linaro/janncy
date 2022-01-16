#ifndef JANNCY_INPUT_H_
#define JANNCY_INPUT_H_

#include <vector>

#include "include/flow_node.h"

namespace janncy {

class FlowVisitor;

class Input : public FlowNode {
 public:
  Input(std::vector<int> shape);

  void Accept(FlowVisitor& visitor) override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

 private:
  std::vector<int> shape_;
};

}  // namespace janncy

#endif  // JANNCY_INPUT_H_
