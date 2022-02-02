#include "include/onnx_utils.h"

#include <experimental/filesystem>
#include <fstream>
#include <memory>
#include <vector>

#include "include/shape.h"
#include "include/tensor.h"

namespace janncy {

namespace onnx_utils {

bool file_exists(const std::string& filename) {
  return std::experimental::filesystem::exists(filename);
}

const onnx::AttributeProto& attribute(const onnx::NodeProto& node_proto,
                                      const std::string& attr_name) {
  for (const auto& attr : node_proto.attribute()) {
    if (attr.name() == attr_name) {
      return attr;
    }
  }
  PANIC("Attribute ", attr_name, " not present in NodeProto ",
        node_proto.name());
}

const onnx::AttributeProto& typed_attribute(
    const onnx::NodeProto& node_proto, const std::string& attr_name,
    const onnx::AttributeProto::AttributeType& attr_type) {
  const auto& attr = attribute(node_proto, attr_name);
  PANIC_IF(attr.type() != attr_type, "Attribute type mismatch!");
  return attr;
}

int int_attribute(const onnx::NodeProto& node_proto,
                  const std::string& attr_name) {
  const auto& attr =
      typed_attribute(node_proto, attr_name, onnx::AttributeProto::INT);
  return attr.i();
}

std::unique_ptr<onnx::ModelProto> ParseModel(const std::string& onnx_filename) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  PANIC_IF(!file_exists(onnx_filename));

  std::ifstream in(onnx_filename, std::ios::ate | std::ios::binary);
  std::streamsize size = in.tellg();
  in.seekg(0, std::ios::beg);

  std::vector<char> buffer(size);
  in.read(buffer.data(), size);
  auto model = std::make_unique<onnx::ModelProto>();
  ParseProtoFromBytes(model.get(), buffer.data(), size);

  return model;
}

std::unique_ptr<OnnxNode> ReadInitializer(const onnx::TensorProto& ini) {
  Shape shape(ini.dims().begin(), ini.dims().end());
  return std::make_unique<OnnxInitializer>(ini.name(), shape);
}

OwnedOnnxNodeVec LoadInitializers(const onnx::GraphProto& graph_proto) {
  OwnedOnnxNodeVec result;
  for (const auto& ini : graph_proto.initializer()) {
    result.push_back(ReadInitializer(ini));
  }
  return result;
}

std::unique_ptr<OnnxNode> ReadInput(const onnx::ValueInfoProto& node_proto) {
  const auto& type = node_proto.type();
  PANIC_IF(!type.has_tensor_type(), "Only tensor inputs are supported!");
  const auto& tensor_type = type.tensor_type();
  PANIC_IF(!tensor_type.has_shape(), "Input tensor with unknown shape!");
  const auto& tensor_shape = tensor_type.shape();
  // Drops first dimension (batch size)
  Shape shape(tensor_shape.dim_size() - 1);
  for (int i = 0; i + 1 < tensor_shape.dim_size(); ++i) {
    const auto& dim = tensor_shape.dim(i + 1);
    PANIC_IF(!dim.has_dim_value(),
             "Only numeric tensor dimensions are supported (no parameters)");
    shape[i] = dim.dim_value();
  }
  return std::make_unique<OnnxInput>(node_proto.name(), shape);
}

OwnedOnnxNodeVec LoadInputs(const onnx::GraphProto& graph_proto) {
  OwnedOnnxNodeVec result;
  for (const auto& node_proto : graph_proto.input()) {
    result.push_back(ReadInput(node_proto));
  }
  return result;
}

std::unique_ptr<OnnxNode> ReadReluLayer(const onnx::NodeProto& node_proto) {
  PANIC_IF(node_proto.input().size() != 1);
  return std::make_unique<OnnxReluLayer>(
      node_proto.name(), node_proto.input()[0], node_proto.output()[0]);
}

std::unique_ptr<OnnxNode> ReadAddLayer(const onnx::NodeProto& node_proto) {
  PANIC_IF(node_proto.input().size() != 2);
  return std::make_unique<OnnxAddLayer>(
      node_proto.name(), node_proto.input()[1], node_proto.input()[0],
      node_proto.output()[0]);
}

std::vector<int> optional_ints_attribute(const onnx::NodeProto& node_proto,
                                         const std::string& attr_name) {
  auto attr =
      typed_attribute(node_proto, attr_name, onnx::AttributeProto::INTS);
  return std::vector<int>(attr.ints().begin(), attr.ints().end());
}

std::vector<int> strides(const onnx::NodeProto& node_proto) {
  return optional_ints_attribute(node_proto, ONNX_ATTR_STRIDES);
}
std::vector<int> padding(const onnx::NodeProto& node_proto) {
  return optional_ints_attribute(node_proto, ONNX_ATTR_PADDING);
}

std::unique_ptr<OnnxNode> ReadConvLayer(const onnx::NodeProto& node_proto) {
  PANIC_IF(node_proto.input().size() != 2 && node_proto.input().size() != 3);
  if (node_proto.input().size() == 3) {
    std::cerr << "We do not handle bias in ConvLayer yet!" << std::endl;
  }
  return std::make_unique<OnnxConvLayer>(
      node_proto.name(), node_proto.input()[0], node_proto.input()[1],
      node_proto.output()[0], strides(node_proto), padding(node_proto));
}

Shape kernel_shape(const onnx::NodeProto& node_proto) {
  return Shape(optional_ints_attribute(node_proto, ONNX_ATTR_KERNEL_SHAPE));
}

KernelAttributes ReadKernelAttributes(const onnx::NodeProto& node_proto) {
  return KernelAttributes(kernel_shape(node_proto), strides(node_proto),
                          padding(node_proto));
}

std::unique_ptr<OnnxNode> ReadMaxPoolLayer(const onnx::NodeProto& node_proto) {
  PANIC_IF(node_proto.input().size() != 1);
  return std::make_unique<OnnxAveragePoolLayer>(
      node_proto.name(), node_proto.input()[0], node_proto.output()[0],
      ReadKernelAttributes(node_proto));
}

std::unique_ptr<OnnxNode> ReadAveragePoolLayer(
    const onnx::NodeProto& node_proto) {
  PANIC_IF(node_proto.input().size() != 1);
  return std::make_unique<OnnxAveragePoolLayer>(
      node_proto.name(), node_proto.input()[0], node_proto.output()[0],
      ReadKernelAttributes(node_proto));
}

std::unique_ptr<OnnxNode> ReadGlobalAveragePoolLayer(
    const onnx::NodeProto& node_proto) {
  PANIC_IF(node_proto.input().size() != 1);
  return std::make_unique<OnnxGlobalAveragePoolLayer>(
      node_proto.name(), node_proto.input()[0], node_proto.output()[0]);
}

std::unique_ptr<OnnxNode> ReadFullyConnectedLayer(
    const onnx::NodeProto& node_proto) {
  PANIC_IF(node_proto.input().size() != 2 && node_proto.input().size() != 3);
  if (node_proto.input().size() == 3) {
    std::cerr << "We do not handle bias in FullyConnectedLayer yet!"
              << std::endl;
  }
  return std::make_unique<OnnxFullyConnectedLayer>(
      node_proto.name(), node_proto.input()[0], node_proto.input()[1],
      node_proto.output()[0]);
}

std::unique_ptr<OnnxNode> ReadFlattenLayer(const onnx::NodeProto& node_proto) {
  PANIC_IF(node_proto.input().size() != 1);
  int axis = int_attribute(node_proto, ONNX_ATTR_AXIS);
  return std::make_unique<OnnxFlattenLayer>(
      node_proto.name(), node_proto.input()[0], node_proto.output()[0], axis);
}

std::unique_ptr<OnnxNode> ReadComputeNode(const onnx::NodeProto& node_proto) {
  PANIC_IF(node_proto.output().size() == 0,
           "At least one output expected for each NodeProto!");
  if (node_proto.output().size() > 1) {
    std::cerr
        << "WARNING: Ignoring all outputs except first one, but ONNX node "
        << node_proto.name() << " has " << node_proto.output().size()
        << " outputs!" << std::endl;
  }
  if (node_proto.op_type() == "Add") {
    return ReadAddLayer(node_proto);
  } else if (node_proto.op_type() == "AveragePool") {
    return ReadAveragePoolLayer(node_proto);
  } else if (node_proto.op_type() == "Conv") {
    return ReadConvLayer(node_proto);
  } else if (node_proto.op_type() == "Flatten") {
    return ReadFlattenLayer(node_proto);
  } else if (node_proto.op_type() == "Gemm") {
    return ReadFullyConnectedLayer(node_proto);
  } else if (node_proto.op_type() == "GlobalAveragePool") {
    return ReadGlobalAveragePoolLayer(node_proto);
  } else if (node_proto.op_type() == "MaxPool") {
    return ReadMaxPoolLayer(node_proto);
  } else if (node_proto.op_type() == "Relu") {
    return ReadReluLayer(node_proto);
  } else {
    PANIC("ONNX operation `" + node_proto.op_type() + "' not supported!");
  }
}

OwnedOnnxNodeVec LoadComputeNodes(const onnx::GraphProto& graph_proto) {
  OwnedOnnxNodeVec result;
  for (const auto& node_proto : graph_proto.node()) {
    result.push_back(ReadComputeNode(node_proto));
  }
  return result;
}

OwnedOnnxNodeVec MoveIntoFrom(OwnedOnnxNodeVec destination,
                              OwnedOnnxNodeVec source) {
  destination.insert(destination.end(), std::make_move_iterator(source.begin()),
                     std::make_move_iterator(source.end()));
  return destination;
}

OwnedOnnxNodeVec ReadOnnxNodes(const onnx::GraphProto& graph_proto) {
  auto initializers = LoadInitializers(graph_proto);
  auto inputs = LoadInputs(graph_proto);
  auto compute_nodes = LoadComputeNodes(graph_proto);
  OwnedOnnxNodeVec result;
  result.reserve(initializers.size() + inputs.size() + compute_nodes.size());
  result = MoveIntoFrom(std::move(result), std::move(initializers));
  result = MoveIntoFrom(std::move(result), std::move(inputs));
  result = MoveIntoFrom(std::move(result), std::move(compute_nodes));
  return result;
}

onnx::GraphProto FileToGraphProto(const std::string& onnx_filename) {
  auto model = ParseModel(onnx_filename);
  PANIC_IF(!model->has_graph(), "Model does not have a graph!");
  return model->graph();
}

OwnedOnnxNodeVec FileToOnnxNodeVec(const std::string& onnx_filename) {
  onnx::GraphProto graph = FileToGraphProto(onnx_filename);
  auto result = ReadOnnxNodes(graph);
  google::protobuf::ShutdownProtobufLibrary();
  return result;
}
std::unordered_map<std::string, Tensor> ReadWeights(
    const onnx::GraphProto& graph_proto) {
  std::unordered_map<std::string, Tensor> result;
  for (const auto& ini : graph_proto.initializer()) {
    Shape shape(ini.dims().begin(), ini.dims().end());
    result.emplace(ini.name(), Tensor(onnx::ParseData<float>(&ini), shape));
  }
  return result;
}

}  // namespace onnx_utils

}  // namespace janncy

