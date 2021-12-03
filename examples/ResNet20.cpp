#include <iostream>

#include "../src/include/Flow.hpp"

FlowNode* conv_bn(Flow& resnet, FlowNode* parent, Tensor filter) {
    auto conv = resnet.conv_layer(parent, filter, 1, true);
    auto bn = resnet.batch_normalization(conv);
    return bn;
}

FlowNode* conv_bn_relu(Flow& resnet, FlowNode* parent, Tensor filter) {
    auto bn = conv_bn(resnet, parent, filter);
    auto relu = resnet.reLU(bn);
    return relu;
}

FlowNode* conv2(Flow& resnet, FlowNode* parent) {
    auto res1 = conv_bn_relu(resnet, parent, Tensor({16, 3, 3}));
    auto res2_1_0 = conv_bn_relu(resnet, res1, Tensor({16, 3, 3}));
    auto res2_1 = conv_bn(resnet, res2_1_0, Tensor({16, 3, 3}));
    auto add2_1 = resnet.add(res1, res2_1);
    auto relu2_1 = resnet.reLU(add2_1);
    return relu2_1;
}

FlowNode* conv3_1(Flow& resnet, FlowNode* parent) {
    auto conv_side = resnet.conv_layer(parent, Tensor({32, 3, 3}), 2, true);
    auto bn3_1_1 = resnet.conv_layer(parent, Tensor({32, 3, 3}), 2, true);
    auto relu3_1_1 = resnet.reLU(bn3_1_1);
    auto conv3_1_2 = resnet.conv_layer(relu3_1_1, Tensor({32, 3, 3}), 1, true);
    auto bn3_1 = resnet.batch_normalization(conv3_1_2);
    auto add3_1 = resnet.add(conv_side, bn3_1);
    auto conv3_1_out = resnet.reLU(add3_1);
    return conv3_1_out;
}

FlowNode* conv3(Flow& resnet, FlowNode* parent) {
    auto bn_1 = resnet.conv_layer(parent, Tensor({32, 3, 3}), 1, true);
    auto relu3_1 = resnet.reLU(bn_1);
    auto conv3_2 = resnet.conv_layer(relu3_1, Tensor({32, 3, 3}), 1, true);
    auto bn_2 = resnet.batch_normalization(conv3_2);
    auto add_1 = resnet.add(parent, bn_2);
    auto conv_out = resnet.reLU(add_1);
    return conv_out;
}

FlowNode* conv4_1(Flow& resnet, FlowNode* parent) {
    auto conv_side = resnet.conv_layer(parent, Tensor({64, 3, 3}), 2, true);
    auto bn3_1_1 = resnet.conv_layer(parent, Tensor({64, 3, 3}), 2, true);
    auto relu3_1_1 = resnet.reLU(bn3_1_1);
    auto conv3_1_2 = resnet.conv_layer(relu3_1_1, Tensor({64, 3, 3}), 1, true);
    auto bn3_1 = resnet.batch_normalization(conv3_1_2);
    auto add3_1 = resnet.add(conv_side, bn3_1);
    auto conv3_1_out = resnet.reLU(add3_1);
    return conv3_1_out;
}

FlowNode* conv4(Flow& resnet, FlowNode* parent) {
    auto bn_1 = resnet.conv_layer(parent, Tensor({64, 3, 3}), 1, true);
    auto relu3_1 = resnet.reLU(bn_1);
    auto conv3_2 = resnet.conv_layer(relu3_1, Tensor({64, 3, 3}), 1, true);
    auto bn_2 = resnet.batch_normalization(conv3_2);
    auto add_1 = resnet.add(parent, bn_2);
    auto conv_out = resnet.reLU(add_1);
    return conv_out;
}

int main() {
    auto resnet = Flow();

    auto input_tensor = resnet.input(Tensor({3, 32, 32}));

    auto conv2_1 = conv2(resnet, input_tensor);
    auto conv2_2 = conv2(resnet, conv2_1);
    auto conv2_3 = conv2(resnet, conv2_2);

    auto conv3_1_out = conv3_1(resnet, conv2_3);
    auto conv3_2 = conv3(resnet, conv3_1_out);
    auto conv3_3 = conv3(resnet, conv3_2);

    auto conv4_1_out = conv4_1(resnet, conv3_3);
    auto conv4_2 = conv4(resnet, conv4_1_out);
    auto conv4_3 = conv4(resnet, conv4_2);

    auto ap = resnet.average_pool(conv4_3, Tensor({64, 8, 8}), 1, false);

    auto fc = resnet.fully_connected(ap, Tensor({64, 10}));

    fc->str();
    resnet.draw();
}
