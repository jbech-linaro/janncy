#include "include/flow_utils.hpp"

#include "include/Add.hpp"
#include "include/AveragePool.hpp"
#include "include/ConvLayer.hpp"
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

void print_dim(const ::onnx::TensorShapeProto_Dimension &dim) {
    switch (dim.value_case()) {
        case onnx::TensorShapeProto_Dimension::ValueCase::kDimParam:
            std::cout << dim.dim_param();
            break;
        case onnx::TensorShapeProto_Dimension::ValueCase::kDimValue:
            std::cout << dim.dim_value();
            break;
        default:
            panic("print_dim()'s case statements!");
    }
}

void print_io_info(
    const ::google::protobuf::RepeatedPtrField< ::onnx::ValueInfoProto> &info) {
    for (auto input_data : info) {
        auto shape = input_data.type().tensor_type().shape();
        std::cout << "  " << input_data.name() << ":";
        std::cout << "[";
        if (shape.dim_size() != 0) {
            int size = shape.dim_size();
            for (int i = 0; i < size - 1; ++i) {
                print_dim(shape.dim(i));
                std::cout << ", ";
            }
            print_dim(shape.dim(size - 1));
        }
        std::cout << "]\n";
    }
}

bool is_substring(std::string superstring, std::string substring) {
    return (superstring.find(substring) != std::string::npos);
}

/**
 * Specification of ONNX operations:
 * https://github.com/onnx/onnx/blob/master/docs/Operators.md#MaxPool
 */
void create_node(Flow *flow, onnx::NodeProto &node) {
    FlowNode *new_node;
    auto parents = std::vector<FlowNode *>{};
    auto weights = std::vector<std::vector<int> >{};
    std::cout << node.name() << ": ";
    for (auto in : node.input()) {
        std::cout << in << ", ";
    }
    std::cout << " -> ";
    for (auto out : node.output()) {
        std::cout << out << ", ";
    }
    std::cout << std::endl;

    for (auto node : node.input()) {
        if (is_substring(node, "input") &&
            flownode_map.find(std::string(node)) == flownode_map.end()) {
            flownode_map.insert(std::make_pair(
                std::string(node), input(flow, std::vector<int>{3, 224, 224})));
        }
    }
    std::transform(
        node.input().begin(), node.input().end(), std::back_inserter(parents),
        [&](auto parent) {
            if (flownode_map.find(std::string(parent)) != flownode_map.end()) {
                return flownode_map.at(std::string(parent));
            } else {
                return (FlowNode *)nullptr;
            }
        });
    std::transform(
        node.input().begin(), node.input().end(), std::back_inserter(weights),
        [&](auto weight) {
            if (shape_map.find(std::string(weight)) != shape_map.end()) {
                return shape_map.at(std::string(weight));
            } else {
                return std::vector<int>{};
            }
        });

    if (node.op_type() == "Relu") {
        new_node = relu(flow, parents[0]);
    } else if (node.op_type() == "Conv") {
        std::cout << ini_map[node.input(1)].float_data().size() << std::endl;
        std::cout << "has_data_type: " << ini_map[node.input(1)].data_type()
                  << std::endl;
        for (auto dim : ini_map[node.input(1)].dims()) {
            std::cout << dim << ", ";
        }
        std::cout << std::endl;
        auto real_weights = onnx::ParseData<float>(&ini_map.at(node.input(1)));
        std::cout << "number of weights: " << real_weights.size() << std::endl;
        auto stride = std::vector<int>(parents[0]->shape().size() + 1, 1);
        auto padding = std::vector<int>(parents[0]->shape().size() + 1, 0);
        for (auto attr : node.attribute()) {
            if (attr.name() == "stride") {
                stride = std::vector<int>{};
                std::transform(attr.ints().begin(), attr.ints().end(),
                               std::back_inserter(stride),
                               [&](auto x) { return x; });
            }
            if (attr.name() == "pads") {
                padding = std::vector<int>{};
                std::transform(attr.ints().begin(), attr.ints().end(),
                               std::back_inserter(padding),
                               [&](auto x) { return x; });
            }
        }
        new_node = conv_layer(flow, parents[0], weights[1], stride, padding);
    } else if (node.op_type() == "Add") {
        new_node = add(flow, std::vector<FlowNode *>{parents[0], parents[1]});
    } else if (node.op_type() == "MaxPool") {
        auto stride = std::vector<int>(parents[0]->shape().size() + 1, 1);
        auto padding = std::vector<int>(parents[0]->shape().size() + 1, 0);
        auto tensor = std::vector<int>{};
        for (auto attr : node.attribute()) {
            if (attr.name() == "auto_pad") {
                panic(
                    "`auto_pad' is a deprecated ONNX attributed that is not "
                    "supported! Please explicitly list padding strategy under "
                    "the `pads' attribute.");
            }
            if (attr.name() == "ceil_mode") {
                panic("`ceil_mode' not supported yet!");
            }
            if (attr.name() == "strides") {
                stride = std::vector<int>{};
                std::transform(attr.ints().begin(), attr.ints().end(),
                               std::back_inserter(stride),
                               [&](auto x) { return x; });
            }
            if (attr.name() == "pads") {
                std::cout << "PADDING: ";
                padding = std::vector<int>{};
                std::transform(attr.ints().begin(), attr.ints().end(),
                               std::back_inserter(padding),
                               [&](auto x) { return x; });
                for (auto pad : attr.ints()) {
                    std::cout << pad << ", ";
                }
                std::cout << "END PAD" << std::endl;
            }
            if (attr.name() == "kernel_shape") {
                for (auto dim : attr.ints()) {
                    tensor.push_back(dim);
                }
            }
        }
        new_node = max_pool(flow, parents[0], tensor, stride, padding);
    } else if (node.op_type() == "AveragePool") {
        auto stride = std::vector<int>(parents[0]->shape().size() + 1, 1);
        auto padding = std::vector<int>(parents[0]->shape().size() + 1, 0);
        auto tensor = std::vector<int>{};
        for (auto attr : node.attribute()) {
            if (attr.name() == "auto_pad") {
                panic(
                    "`auto_pad' is a deprecated ONNX attributed that is not "
                    "supported! Please explicitly list padding strategy under "
                    "the `pads' attribute.");
            }
            if (attr.name() == "ceil_mode") {
                panic("`ceil_mode' not supported yet!");
            }
            if (attr.name() == "strides") {
                stride = std::vector<int>{};
                std::transform(attr.ints().begin(), attr.ints().end(),
                               std::back_inserter(stride),
                               [&](auto x) { return x; });
            }
            if (attr.name() == "pads") {
                padding = std::vector<int>{};
                std::transform(attr.ints().begin(), attr.ints().end(),
                               std::back_inserter(padding),
                               [&](auto x) { return x; });
            }
            if (attr.name() == "kernel_shape") {
                for (auto dim : attr.ints()) {
                    tensor.push_back(dim);
                }
            }
        }
        new_node = average_pool(flow, parents[0], tensor, stride, padding);
    } else if (node.op_type() == "GlobalAveragePool") {
        std::cout << parents[0]->shape().size() << std::endl;
        auto tensor = std::vector<int>(parents[0]->shape().begin() + 1,
                                       parents[0]->shape().end());
        new_node =
            average_pool(flow, parents[0], tensor,
                         std::vector<int>(parents[0]->shape().size(), 1),
                         std::vector<int>(parents[0]->shape().size(), 0));
    } else if (node.op_type() == "Gemm") {
        new_node = fully_connected(flow, parents[0], weights[1]);
    } else if (node.op_type() == "Flatten") {
        int axis = 1;
        for (auto attr : node.attribute()) {
            if (attr.name() == "axis") {
                axis = attr.i();
                if (axis < 1) {
                    panic(
                        "Nikola only knows how to support axis >= 1. If you "
                        "need axis < 1, please create an issue!");
                }
            }
        }
        new_node = flatten(flow, parents[0], axis);
    } else {
        panic("ONNX operation `" + node.op_type() + "' not supported!");
    }
    flownode_map.insert(std::make_pair(std::string(node.output(0)), new_node));
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
    if (graph.input().size() > 0) {
        flownode_map.insert(std::make_pair(
            graph.input(0).name(), input(flow, std::vector<int>{3, 224, 224})));
    }
    for (auto ini : graph.initializer()) {
        ini_map.insert(std::make_pair(ini.name(), ini));
        std::vector<int> dim_vec;
        for (auto dim : ini.dims()) {
            dim_vec.push_back(dim);
        }
        shape_map.insert(std::make_pair(ini.name(), dim_vec));
    }

    for (auto node : graph.node()) {
        create_node(flow, node);
    }
    flow->draw("test");
}
