#ifndef JANNCY_BATCH_NORMALIZATION_H_
#define JANNCY_BATCH_NORMALIZATION_H_

#include <string>
#include <vector>

#include "include/flow_node.h"

class FlowVisitor;

namespace janncy {

class BatchNormalization : public FlowNode {
 public:
  BatchNormalization(std::vector<int> shape);

  void Accept(FlowVisitor& visitor) override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

 private:
  std::vector<int> shape_;
};

}  // namespace janncy

#endif  // JANNCY_BATCH_NORMALIZATION_H_
