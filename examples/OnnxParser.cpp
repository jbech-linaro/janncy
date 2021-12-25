#include "include/flow_utils.hpp"

#include "include/Add.hpp"
#include "include/AveragePool.hpp"
#include "include/ConvLayer.hpp"
#include "include/CtGraph.hpp"
#include "include/Flatten.hpp"
#include "include/Flow.hpp"
#include "include/FullyConnected.hpp"
#include "include/Input.hpp"
#include "include/MaxPool.hpp"
#include "include/Panic.hpp"
#include "include/ReLU.hpp"

#include "onnx/defs/tensor_proto_util.h"
#include "onnx/onnx_pb.h"
#include "onnx/proto_utils.h"

#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, FlowNode *> flownode_map;
std::unordered_map<std::string, std::vector<int> > shape_map;
std::unordered_map<std::string, onnx::TensorProto> ini_map;

std::string ATTR_STRIDES = "strides";
std::string ATTR_PADDING = "pads";
std::string ATTR_AUTO_PAD = "auto_pad";
std::string ATTR_KERNEL_SHAPE = "kernel_shape";
std::string ATTR_AXIS = "axis";

bool is_substring(std::string superstring, std::string substring) {
    return (superstring.find(substring) != std::string::npos);
}

std::vector<FlowNode *> get_parents(onnx::NodeProto &node) {
    auto parents = std::vector<FlowNode *>{};
    std::transform(
        node.input().begin(), node.input().end(), std::back_inserter(parents),
        [&](auto parent) {
            if (flownode_map.find(std::string(parent)) != flownode_map.end()) {
                return flownode_map.at(std::string(parent));
            } else {
                return (FlowNode *)nullptr;
            }
        });
    return parents;
}

std::vector<std::vector<int> > get_weights(onnx::NodeProto &node) {
    auto weights = std::vector<std::vector<int> >{};
    std::transform(
        node.input().begin(), node.input().end(), std::back_inserter(weights),
        [&](auto weight) {
            if (shape_map.find(std::string(weight)) != shape_map.end()) {
                return shape_map.at(std::string(weight));
            } else {
                return std::vector<int>{};
            }
        });
    return weights;
}

void create_relu(Flow *flow, onnx::NodeProto &node) {
    assert(node.op_type() == "Relu");
    auto parents = get_parents(node);
    auto new_node = relu(flow, parents[0]);
    flownode_map.insert(std::make_pair(std::string(node.output(0)), new_node));
}

int get_attribute_int(onnx::NodeProto &node, const std::string &attr_name) {
    for (auto attr : node.attribute()) {
        if (attr.name() == attr_name) {
            return attr.i();
        }
    }
    panic("Attribute `" + attr_name + "' not found!");
    return 0;
}

std::vector<int> get_attribute_ints(onnx::NodeProto &node,
                                    const std::string &attr_name) {
    for (auto attr : node.attribute()) {
        if (attr.name() == attr_name) {
            auto result = std::vector<int>{};
            for (auto value : attr.ints()) {
                result.push_back(value);
                std::cout << value << ", ";
            }
            std::cout << std::endl;
            return result;
        }
    }
    panic("Attribute `" + attr_name + "' not found!");
    return std::vector<int>{};
}

bool attribute_exists(onnx::NodeProto &node, const std::string &attr_name) {
    return std::any_of(node.attribute().begin(), node.attribute().end(),
                       [&](auto x) { return x.name() == attr_name; });
}

std::vector<int> get_strides(onnx::NodeProto &node) {
    auto parents = get_parents(node);
    auto strides = std::vector<int>(parents[0]->shape().size() + 1, 1);
    if (attribute_exists(node, ATTR_STRIDES)) {
        strides = get_attribute_ints(node, ATTR_STRIDES);
    }
    return strides;
}

std::vector<int> get_padding(onnx::NodeProto &node) {
    auto parents = get_parents(node);
    auto padding = std::vector<int>(parents[0]->shape().size() + 1, 0);
    if (attribute_exists(node, ATTR_PADDING)) {
        padding = get_attribute_ints(node, ATTR_PADDING);
    }
    return padding;
}

void create_conv(Flow *flow, onnx::NodeProto &node) {
    assert(node.op_type() == "Conv");
    auto parents = get_parents(node);
    auto weights = get_weights(node);
    auto real_weights = onnx::ParseData<float>(&ini_map.at(node.input(1)));
    auto strides = get_strides(node);
    auto padding = get_padding(node);
    auto new_node = conv_layer(flow, parents[0], weights[1], strides, padding);
    flownode_map.insert(std::make_pair(std::string(node.output(0)), new_node));
}

void create_add(Flow *flow, onnx::NodeProto &node) {
    auto parents = get_parents(node);
    auto new_node = add(flow, {parents[0], parents[1]});
    flownode_map.insert(std::make_pair(std::string(node.output(0)), new_node));
}

void create_max_pool(Flow *flow, onnx::NodeProto &node) {
    auto parents = get_parents(node);
    auto weights = get_weights(node);
    auto strides = get_strides(node);
    auto padding = get_padding(node);
    auto kernel_shape = get_attribute_ints(node, ATTR_KERNEL_SHAPE);
    auto new_node = max_pool(flow, parents[0], kernel_shape, strides, padding);
    flownode_map.insert(std::make_pair(std::string(node.output(0)), new_node));
}

void create_average_pool(Flow *flow, onnx::NodeProto &node) {
    auto parents = get_parents(node);
    auto strides = get_strides(node);
    auto padding = get_padding(node);
    auto kernel_shape = get_attribute_ints(node, ATTR_KERNEL_SHAPE);
    auto new_node =
        average_pool(flow, parents[0], kernel_shape, strides, padding);
    flownode_map.insert(std::make_pair(std::string(node.output(0)), new_node));
}

void create_global_average_pool(Flow *flow, onnx::NodeProto &node) {
    auto parents = get_parents(node);
    std::cout << parents[0]->shape().size() << std::endl;
    std::vector<int> tensor(parents[0]->shape().begin() + 1,
                            parents[0]->shape().end());
    std::cout << "kernel shape size: " << tensor.size() << std::endl;
    auto new_node =
        average_pool(flow, parents[0], tensor,
                     std::vector<int>(parents[0]->shape().size(), 1),
                     std::vector<int>(parents[0]->shape().size(), 0));
    flownode_map.insert(std::make_pair(std::string(node.output(0)), new_node));
}
void create_fully_connected(Flow *flow, onnx::NodeProto &node) {
    auto parents = get_parents(node);
    auto weights = get_weights(node);
    auto new_node = fully_connected(flow, parents[0], weights[1]);
    flownode_map.insert(std::make_pair(std::string(node.output(0)), new_node));
}
int get_axis(onnx::NodeProto &node) {
    int axis = 1;
    if (attribute_exists(node, ATTR_AXIS)) {
        axis = get_attribute_int(node, ATTR_AXIS);
    }
    return axis;
}

void create_flatten(Flow *flow, onnx::NodeProto &node) {
    auto parents = get_parents(node);
    auto axis = get_axis(node);
    if (axis < 1) {
        panic(
            "Nikola only knows how to support axis >= 1. If "
            "you "
            "need axis < 1, please create an issue!");
    }
    auto new_node = flatten(flow, parents[0], axis);
    flownode_map.insert(std::make_pair(std::string(node.output(0)), new_node));
}
/**
 * Specification of ONNX operations:
 * https://github.com/onnx/onnx/blob/master/docs/Operators.md#MaxPool
 */
void create_node(Flow *flow, onnx::NodeProto &node) {
    if (node.op_type() == "Relu") {
        create_relu(flow, node);
    } else if (node.op_type() == "Conv") {
        create_conv(flow, node);
    } else if (node.op_type() == "Add") {
        create_add(flow, node);
    } else if (node.op_type() == "MaxPool") {
        create_max_pool(flow, node);
    } else if (node.op_type() == "AveragePool") {
        create_average_pool(flow, node);
    } else if (node.op_type() == "GlobalAveragePool") {
        create_global_average_pool(flow, node);
    } else if (node.op_type() == "Gemm") {
        create_fully_connected(flow, node);
    } else if (node.op_type() == "Flatten") {
        create_flatten(flow, node);
    } else {
        panic("ONNX operation `" + node.op_type() + "' not supported!");
    }
}

int main(int argc, char **argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    if (argc != 2) {
        panic(
            "Please provide filepath to *.onnx file as command-line "
            "argument!");
    }
    std::string filename = argv[1];
    if (!std::experimental::filesystem::exists(
            std::experimental::filesystem::path(filename))) {
        panic("ONNX file does not exist!");
    }
    std::ifstream in(filename, std::ios::ate | std::ios::binary);
    std::streamsize size = in.tellg();
    in.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    in.read(buffer.data(), size);
    std::unique_ptr<onnx::ModelProto> model(new onnx::ModelProto());
    ParseProtoFromBytes(model.get(), buffer.data(), size);
    google::protobuf::ShutdownProtobufLibrary();

    /**
     * TODO(nsamar): For some reason, I get a logic_error for the
     * model->graph() line if I do not print the value of has_graph(). This
     * only occurs when running on resnet18.onnx.
     */
    std::cout << model->has_graph() << std::endl;
    if (!model->has_graph()) {
        panic("Model does not have a graph!");
    }
    auto graph = model->graph();

    Flow *flow = new Flow();
    // TODO(nsamar): the input dimensions should be read out, not assumed to be
    // {3, 224, 224}
    for (auto ini : graph.initializer()) {
        ini_map.insert(std::make_pair(ini.name(), ini));
        std::vector<int> dim_vec;
        for (auto dim : ini.dims()) {
            dim_vec.push_back(dim);
        }
        shape_map.insert(std::make_pair(ini.name(), dim_vec));
    }
    for (auto node : graph.input()) {
        flownode_map.insert(std::make_pair(
            node.name(), input(flow, std::vector<int>{3, 224, 224})));
    }

    for (auto node : graph.node()) {
        create_node(flow, node);
    }
    flow->draw("test");
    auto ct_graph = flow->cipherfy();
    ct_graph->draw("ct_graph");
}
