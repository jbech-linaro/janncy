#include "include/flow_node.h"

#include <sstream>
#include <string>

namespace janncy {

std::string FlowNode::str() const {
  std::stringstream result;
  result << "[" << this << "] ";
  result << op_type();
  if (op_type() != "Input") {
    result << "(";
    for (auto& value : shape()) {
      result << value << ", ";
    }
    result << ")";
  }
  return result.str();
}

}  // namespace janncy
