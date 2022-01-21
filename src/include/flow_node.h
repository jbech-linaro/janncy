#ifndef JANNCY_FLOW_NODE_H_
#define JANNCY_FLOW_NODE_H_

#include <string>
#include <vector>

namespace janncy {

class FlowVisitor;

class FlowNode {
 public:
  virtual void Accept(FlowVisitor& visitor) const = 0;
  virtual std::string op_type() const = 0;
  virtual std::vector<int> shape() const = 0;

  virtual ~FlowNode() {}
};

std::ostream& operator<<(std::ostream& stream, const FlowNode& node);

}  // namespace janncy

#endif  // JANNCY_FLOW_NODE_H_
