#include "include/Flow.hpp"

#include "include/FlowNode.hpp"
#include "include/Tensor.hpp"
#include "include/BatchNormalization.hpp"
#include "include/ConvLayer.hpp"
#include "include/FullyConnected.hpp"
#include "include/AveragePool.hpp"
#include "include/Input.hpp"
#include "include/ReLU.hpp"
#include "include/Add.hpp"

#include <sstream>
#include <cassert>

FlowNode* Flow::input(Tensor input_tensor) {
    auto input_node = new Input(input_tensor);
    add_node(input_node);
    return input_node;
}

FlowNode* Flow::add(FlowNode* parent0, FlowNode* parent1) {
    FlowNode* a = new Add(parent0, parent1);
    parent0->add_child(a);
    parent1->add_child(a);
    add_node(a);
    return a;
}

FlowNode* Flow::average_pool(FlowNode* parent, Tensor pool, int stride, bool padded) {
    auto input_tensor = parent->output_tensor();
    FlowNode* ap = new AveragePool(parent, pool, stride, padded);
    parent->add_child(ap);
    add_node(ap);
    return ap;
}

FlowNode* Flow::conv_layer(FlowNode* parent, Tensor filter, int stride, bool padded) {
    auto input_tensor = parent->output_tensor();
    FlowNode* cl = new ConvLayer(parent, filter, stride, padded);
    parent->add_child(cl);
    add_node(cl);
    return cl;
}

FlowNode* Flow::reLU(FlowNode* parent) {
    FlowNode* relu = new ReLU(parent);
    parent->add_child(relu);
    add_node(relu);
    return relu;
}

FlowNode* Flow::batch_normalization(FlowNode* parent) {
    FlowNode* bn = new BatchNormalization(parent);
    parent->add_child(bn);
    add_node(bn);
    return bn;
}

FlowNode* Flow::fully_connected(FlowNode* parent, Tensor matrix) {
    FlowNode* fc = new FullyConnected(parent, matrix);
    parent->add_child(fc);
    add_node(fc);
    return fc;
}

