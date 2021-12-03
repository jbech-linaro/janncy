#include "include/Flow.hpp"

#include "include/FlowNode.hpp"
#include "include/Tensor.hpp"
#include "include/BatchNormalization.hpp"
#include "include/ConvLayer.hpp"
#include "include/FullyConnected.hpp"
#include "include/Input.hpp"

#include <sstream>
#include <cassert>

FlowNode* Flow::input(Tensor input_tensor) {
    auto input_node = new Input(input_tensor);
    nodes.push_back(input_node);
    return input_node;
}

FlowNode* Flow::average_pool(FlowNode* parent, Tensor pool, int stride) {
    auto input_tensor = parent->output_tensor();
    FlowNode* ap = new ConvLayer(parent, pool, stride);
    parent->add_child(ap);
    nodes.push_back(ap);
    return ap;
}

FlowNode* Flow::conv_layer(FlowNode* parent, Tensor filter, int stride) {
    auto input_tensor = parent->output_tensor();
    FlowNode* cl = new ConvLayer(parent, filter, stride);
    parent->add_child(cl);
    nodes.push_back(cl);
    return cl;
}

FlowNode* Flow::batch_normalization(FlowNode* parent) {
    FlowNode* bn = new BatchNormalization(parent);
    parent->add_child(bn);
    nodes.push_back(bn);
    return bn;
}

FlowNode* Flow::fully_connected(FlowNode* parent, Tensor matrix) {
    FlowNode* fc = new FullyConnected(parent, matrix);
    parent->add_child(fc);
    nodes.push_back(fc);
    return fc;
}

std::string Flow::str() const {
    std::stringstream result;
    for (auto& node : nodes) {
        result << node->str() << " -> ";
        for (auto& child : node->get_children()) {
            result << child->str() << ", ";
        }
        result << "\n";
    }
    return result.str();
}
