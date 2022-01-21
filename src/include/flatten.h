#ifndef JANNCY_FLATTEN_H_
#define JANNCY_FLATTEN_H_

#include <string>
#include <vector>

#include "include/flow_node.h"
#include "include/shape.h"
namespace janncy {

class FlowVisitor;

class Flatten : public FlowNode {
 public:
  Flatten(const Shape& input_shape);

  void Accept(FlowVisitor& visitor) const override;
  std::string op_type() const override;
  Shape shape() const override;

 private:
  int output_dim_;
};

}  // namespace janncy

#endif  // JANNCY_FLATTEN_H_
