#ifndef JANNCY_FULLY_CONNECTED_H_
#define JANNCY_FULLY_CONNECTED_H_

#include "include/flow_node.h"

namespace janncy {

class FlowVisitor;

class FullyConnected : public FlowNode {
 public:
  FullyConnected(int input_size, int output_size);

  void Accept(FlowVisitor& visitor) override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

  int input_size() const;
  int output_size() const;

 private:
  int input_size_;
  int output_size_;
};

}  // namespace janncy

#endif  // JANNCY_FULLY_CONNECTRED_H_
