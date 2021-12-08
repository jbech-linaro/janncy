#include "include/FlowNode.hpp"

#include <sstream>
#include <string>
#include <vector>

FlowNode::FlowNode(std::vector<FlowNode*> parents, Tensor output_tensor,
                   Flow* flow)
    : Node(parents), output_tensor_(output_tensor), flow_(flow) {}

Tensor FlowNode::output_tensor() const { return output_tensor_; }

Tensor FlowNode::input_tensor() const {
    if (parents_[0]) {
        return parents_[0]->output_tensor_;
    }
    return output_tensor_;
}

void FlowNode::set_name(std::string name) { name_ = name; }

std::string FlowNode::str() const {
    std::stringstream result;
    result << "[" << this << "] ";
    result << type_str();
    if (type_str() != "Input") {
        result << "(";
        auto shape_vec = input_tensor().shape();
        for (auto& value : shape_vec) {
            result << value << ", ";
        }
        result << ")";
    }
    return result.str();
}
