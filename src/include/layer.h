#ifndef JANNCY_LAYER_H_
#define JANNCY_LAYER_H_

#include <string>
#include <vector>

#include "include/shape.h"

namespace janncy {

class FlowVisitor;

class FlowNode {
 public:
  virtual void Accept(FlowVisitor& visitor) const = 0;
  virtual std::string op_type() const = 0;
  virtual Shape shape() const = 0;

  virtual ~FlowNode() {}
};

std::ostream& operator<<(std::ostream& stream, const FlowNode& node);

}  // namespace janncy

#endif  // JANNCY_LAYER_H_