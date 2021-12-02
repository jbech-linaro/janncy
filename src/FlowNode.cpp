#include "include/FlowNode.hpp"

FlowNode::FlowNode(Tensor input_tensor, Tensor output_tensor)
    : input_tensor_(input_tensor), output_tensor_(output_tensor) {}

Tensor FlowNode::output_tensor() const {
    return output_tensor_;
}

Tensor FlowNode::input_tensor() const {
    return input_tensor_;
}
