#ifndef FLOWNODE_HPP_
#define FLOWNODE_HPP_

#include <iostream>
#include <string>
#include <vector>

namespace janncy {

class FlowVisitor;

class FlowNode {
 public:
  virtual void accept(FlowVisitor& visitor) = 0;
  virtual std::string op_type() const = 0;
  virtual std::vector<int> shape() const = 0;

  FlowNode() {}

  virtual ~FlowNode() {}

  std::string str() const;
};

}  // namespace janncy

#endif  // FLOWNODE_HPP_
