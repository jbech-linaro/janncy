#ifndef JANNCY_ADD_H_
#define JANNCY_ADD_H_

#include <vector>

#include "include/flow_node.h"

namespace janncy {

class FlowVisitor;

class Add : public FlowNode {
 public:
  Add(std::vector<int> shape);

  void accept(FlowVisitor& visitor) override;
  std::vector<int> shape() const override;
  std::string op_type() const override;

 private:
  std::vector<int> shape_;
};

}  // namespace janncy

#endif  // JANNCY_ADD_H_
