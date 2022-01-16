#ifndef JANNCY_FLATTEN_H_
#define JANNCY_FLATTEN_H_

#include <string>
#include <vector>

#include "include/flow_node.h"

namespace janncy {

class FlowVisitor;

class Flatten : public FlowNode {
 public:
  Flatten(const std::vector<int>& input_shape);

  void Accept(FlowVisitor& visitor) override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

 private:
  int output_dim_;
};

}  // namespace janncy

#endif  // JANNCY_FLATTEN_H_
