#include "include/FlowNode.hpp"
#include <string>
#include <sstream>

FlowNode::FlowNode(FlowNode* parent, Tensor output_tensor)
    : parent_(parent), output_tensor_(output_tensor) {}

Tensor FlowNode::output_tensor() const {
    return output_tensor_;
}

Tensor FlowNode::input_tensor() const {
    if (parent_) {
        return parent_->output_tensor_;
    }
    return output_tensor_;
}

void FlowNode::add_child(FlowNode* child) {
    children.push_back(child);
}

void FlowNode::set_name(std::string name) {
    name_ = name;
}

std::string FlowNode::str() const {
    std::stringstream result;
    if (name_ != "") {
        result << "[" << name_ << "] ";
    }
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
