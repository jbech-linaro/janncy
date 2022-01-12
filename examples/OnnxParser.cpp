#include "include/flow_utils.hpp"

#include "include/Add.hpp"
#include "include/AveragePool.hpp"
#include "include/Cipherfier.hpp"
#include "include/ConvLayer.hpp"
#include "include/CtGraph.hpp"
#include "include/Flatten.hpp"
#include "include/Flow.hpp"
#include "include/FullyConnected.hpp"
#include "include/Input.hpp"
#include "include/MaxPool.hpp"
#include "include/Panic.hpp"
#include "include/ReLU.hpp"
#include "include/utils.hpp"

#include "onnx/defs/tensor_proto_util.h"
#include "onnx/onnx_pb.h"
#include "onnx/proto_utils.h"

#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace janncy;

std::unordered_map<std::string, FlowNode *> flownode_map;
std::unordered_map<std::string, std::vector<int> > shape_map;
std::unordered_map<std::string, onnx::TensorProto> ini_map;

std::string ATTR_STRIDES = "strides";
std::string ATTR_PADDING = "pads";
std::string ATTR_AUTO_PAD = "auto_pad";
std::string ATTR_KERNEL_SHAPE = "kernel_shape";
std::string ATTR_AXIS = "axis";

const onnx::AttributeProto* get_attribute(const onnx::NodeProto &node,
                                          const std::string &attr_name) {
    for (const auto &attr : node.attribute()) {
        if (attr.name() == attr_name) {
            return &attr;
        }
    }
    return nullptr;
}

const onnx::AttributeProto* get_typed_attribute(
        const onnx::NodeProto &node,
        const std::string &attr_name,
        const onnx::AttributeProto::AttributeType &attr_type) {

    auto attr = get_attribute(node, attr_name);
    if ((attr == nullptr) || (attr->type() != attr_type)) {
        return nullptr;
    } else {
        return attr;
    }
}

bool attribute_exists(const onnx::NodeProto &node, const std::string &attr_name) {
    return get_attribute(node, attr_name) != nullptr;
}

int get_attribute_int(const onnx::NodeProto &node,
                      const std::string &attr_name) {
    auto attr = get_typed_attribute(node, attr_name, onnx::AttributeProto::INT);
    if (attr == nullptr) {
        panic("INT attribute `" + attr_name + "' not found!");
    } else {
        return attr->i();
    }
}

std::vector<int> get_attribute_ints(onnx::NodeProto &node,
                                    const std::string &attr_name) {
    auto attr = get_typed_attribute(node, attr_name, onnx::AttributeProto::INTS);
    if (attr == nullptr) {
        panic("INTS attribute `" + attr_name + "' not found!");
    } else {
        return std::vector<int>(attr->ints().begin(), attr->ints().end());
    }
}

std::vector<FlowNode *> get_parents(onnx::NodeProto &node) {
    auto parents = std::vector<FlowNode *>{};
    for (auto p : node.input()) {
        // alex: `flownode_map[p]` defaults to `nullptr` if element is missing.
        parents.push_back(flownode_map[p]);
    }
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
    std::cerr << "Weights " << weights << "\n";
    return weights;
}


std::vector<int> get_strides(onnx::NodeProto &node) {
    if (attribute_exists(node, ATTR_STRIDES)) {
        return get_attribute_ints(node, ATTR_STRIDES);
    } else {
        auto parent = get_parents(node)[0];
        return std::vector<int>(parent->shape().size() - 1, 1);
    }
}

std::vector<int> get_padding(onnx::NodeProto &node) {
    if (attribute_exists(node, ATTR_PADDING)) {
        return get_attribute_ints(node, ATTR_PADDING);
    } else {
        auto parent = get_parents(node)[0];
        return std::vector<int>((parent->shape().size() - 1) * 2, 0);
    }
}

int get_axis(onnx::NodeProto &node) {
    int axis = 1;
    if (attribute_exists(node, ATTR_AXIS)) {
        axis = get_attribute_int(node, ATTR_AXIS);
    }
    return axis;
}

void create_relu(Flow *flow, onnx::NodeProto &node) {
    assert(node.op_type() == "Relu");
    auto parents = get_parents(node);
    auto new_node = relu(flow, parents[0]);
    flownode_map[node.output(0)] = new_node;
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

std::unique_ptr<onnx::ModelProto> parse_model(const std::string &filepath) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    if (!std::experimental::filesystem::exists(
            std::experimental::filesystem::path(filepath))) {
        panic("ONNX file does not exist!");
    }
    std::ifstream in(filepath, std::ios::ate | std::ios::binary);
    std::streamsize size = in.tellg();
    in.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    in.read(buffer.data(), size);
    auto model = std::make_unique<onnx::ModelProto>();
    ParseProtoFromBytes(model.get(), buffer.data(), size);

    return model;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        panic(
            "Please provide filepath to *.onnx file as command-line "
            "argument!");
    }
    /**
     * TODO(nsamar): For some reason, I get a logic_error for the
     * model->graph() line if I do not print the value of has_graph(). This
     * only occurs when running on resnet18.onnx.
     */
    auto model = parse_model(argv[1]);
    std::cout << model->has_graph() << std::endl;
    if (!model->has_graph()) {
        panic("Model does not have a graph!");
    }
    auto graph = model->graph();

    auto flow = std::make_unique<Flow>();

    for (auto ini : graph.initializer()) {
        ini_map.insert(std::make_pair(ini.name(), ini));
        std::vector<int> dim_vec(ini.dims().begin(), ini.dims().end());
        shape_map[ini.name()] = dim_vec;
    }
    for (const auto &node : graph.input()) {
        const auto &type = node.type();
        if (!type.has_tensor_type()) {
            panic("Only tensor inputs are supported!");
        }
        const auto &tensor_type = type.tensor_type();
        if (!tensor_type.has_shape()) {
            panic("Input tensor with unknown shape!");
        }
        const auto &tensor_shape = tensor_type.shape();

        std::vector<int> shape;
        for (const auto &dim : tensor_shape.dim()) {
            if (!dim.has_dim_value()) {
                panic("Only numeric tensor dimensions are supported "
                      "(no parameters)");
            }
            shape.push_back(dim.dim_value());
        }
        // Drop batch size dimension
        shape.erase(shape.begin());
        flownode_map[node.name()] = input(flow.get(), shape);
    }

    for (auto node : graph.node()) {
        create_node(flow.get(), node);
    }
    flow->draw("test");
    flow->cipherfy();

    google::protobuf::ShutdownProtobufLibrary();
    // ct_graph->draw("ct_graph");
}
