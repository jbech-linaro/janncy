#include "include/FlowNode.hpp"

#include <string>

namespace janncy {

std::string FlowNode::str() const {
  return "";
  /*
  std::stringstream result;
  result << "[" << this << "] ";
  result << op_type_;
  if (op_type_ != "Input") {
      result << "(";
      for (auto& value : output_shape_) {
          result << value << ", ";
      }
      result << ")";
  }
  return result.str();
  */
}

}  // namespace janncy
