#include "include/FlowNode.hpp"

#include "include/FlowVisitor.hpp"

#include <sstream>
#include <string>
#include <vector>

namespace janncy {

template <class T> class Graph;

FlowNode::FlowNode(std::vector<int> output_shape, std::string op_type)
    : output_shape_(output_shape), op_type_(op_type) {}

std::string FlowNode::op_type() const { return op_type_; }

const std::vector<int>& FlowNode::shape() const { return output_shape_; }

std::string FlowNode::str() const {
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
}

}  // namespace janncy
