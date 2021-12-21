#include "include/Panic.hpp"

#include "onnx/onnx.pb.h"

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>

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

int main(int argc, char **argv) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    if (argc != 2) {
        panic("Please provide filepath!");
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
    onnx::ModelProto model;
    model.ParseFromArray(buffer.data(), size);
    google::protobuf::ShutdownProtobufLibrary();

    std::cout << "has graph: " << model.has_graph() << std::endl;
    auto graph = model.graph();

    std::cout << "graph name: " << graph.name() << std::endl;

    std::cout << "graph inputs:\n";
    print_io_info(graph.input());

    std::cout << "graph outputs:\n";
    print_io_info(graph.output());

    for (int i = 0; i < graph.node_size(); ++i) {
        std::cout << graph.node(i).name() << ": ";
        for (auto in : graph.node(i).input()) {
            std::cout << in << ", ";
        }
        std::cout << " -> ";
        for (auto out : graph.node(i).output()) {
            std::cout << out << std::endl;
        }
    }
}
