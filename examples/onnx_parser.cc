#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "onnx/defs/tensor_proto_util.h"
#include "onnx/onnx_pb.h"
#include "onnx/proto_utils.h"

#include "include/cipherfier.h"
#include "include/flow.h"
#include "include/graph.h"
#include "include/onnx_graph.h"
#include "include/panic.h"

using namespace janncy;

std::unordered_map<std::string, FlowNode *> flownode_map;
std::unordered_map<std::string, std::vector<int>> shape_map;

const std::string ATTR_STRIDES = "strides";
const std::string ATTR_PADDING = "pads";
const std::string ATTR_AUTO_PAD = "auto_pad";
const std::string ATTR_KERNEL_SHAPE = "kernel_shape";
const std::string ATTR_AXIS = "axis";

const onnx::AttributeProto *get_attribute(const onnx::NodeProto &node,
                                          const std::string &attr_name) {
  for (const auto &attr : node.attribute()) {
    if (attr.name() == attr_name) {
      return &attr;
    }
  }
  return nullptr;
}

const onnx::AttributeProto *get_typed_attribute(
    const onnx::NodeProto &node, const std::string &attr_name,
    const onnx::AttributeProto::AttributeType &attr_type) {
  auto attr = get_attribute(node, attr_name);
  if ((attr == nullptr) || (attr->type() != attr_type)) {
    return nullptr;
  } else {
    return attr;
  }
}

bool attribute_exists(const onnx::NodeProto &node,
                      const std::string &attr_name) {
  return get_attribute(node, attr_name) != nullptr;
}

int get_attribute_int(const onnx::NodeProto &node,
                      const std::string &attr_name) {
  auto attr = get_typed_attribute(node, attr_name, onnx::AttributeProto::INT);
  PANIC_IF(attr == nullptr, "INT attribute `" + attr_name + "' not found!");
  return attr->i();
}

std::vector<int> get_ints_attribute(onnx::NodeProto &node,
                                    const std::string &attr_name) {
  auto attr = get_typed_attribute(node, attr_name, onnx::AttributeProto::INTS);
  PANIC_IF(attr == nullptr, "INTS attribute `" + attr_name + "' not found!");
  return std::vector<int>(attr->ints().begin(), attr->ints().end());
}
std::vector<int> get_optional_ints_attribute(onnx::NodeProto &node,
                                             const std::string &attr_name) {
  auto attr = get_typed_attribute(node, attr_name, onnx::AttributeProto::INTS);
  if (attr == nullptr) {
    return {};
  } else {
    return std::vector<int>(attr->ints().begin(), attr->ints().end());
  }
}

std::vector<const FlowNode *> get_parent_nodes(onnx::NodeProto &node) {
  std::vector<const FlowNode *> parent_nodes;
  for (auto p : node.input()) {
    auto it = flownode_map.find(p);
    if (it != flownode_map.end()) {
      parent_nodes.push_back(it->second);
    } else {
      parent_nodes.push_back(nullptr);
    }
  }
  return parent_nodes;
}

std::vector<std::vector<int>> get_input_shapes(onnx::NodeProto &onnx_node) {
  std::vector<std::vector<int>> input_shapes;

  for (const std::string &input_name : onnx_node.input()) {
    auto shape_it = shape_map.find(input_name);
    PANIC_IF(shape_it == shape_map.end(), "Unknown input to node",
             onnx_node.name(), input_name);
    input_shapes.push_back(shape_it->second);
  }
  return input_shapes;
}

std::vector<int> get_strides(onnx::NodeProto &onnx_node) {
  return get_optional_ints_attribute(onnx_node, ATTR_STRIDES);
}
std::vector<int> get_padding(onnx::NodeProto &onnx_node) {
  return get_optional_ints_attribute(onnx_node, ATTR_PADDING);
}

FlowNode *CreateRelu(Flow &flow, onnx::NodeProto &onnx_node) {
  const FlowNode *par = get_parent_nodes(onnx_node)[0];
  return flow::CreateRelu(flow, par);
}

FlowNode *CreateAdd(Flow &flow, onnx::NodeProto &onnx_node) {
  return flow::CreateAdd(flow, get_parent_nodes(onnx_node));
}

FlowNode *CreateConv(Flow &flow, onnx::NodeProto &onnx_node) {
  std::vector<std::vector<int>> input_shapes = get_input_shapes(onnx_node);

  // Infer from weights input shape
  std::vector<int> raw_kernel_shape = get_input_shapes(onnx_node)[1];
  int output_channel_cnt = raw_kernel_shape[0];
  PANIC_IF(raw_kernel_shape[1] != input_shapes[0][0]);

  std::vector<int> spatial_kernel_shape(raw_kernel_shape.begin() + 2,
                                        raw_kernel_shape.end());
  KernelAttributes kernel(spatial_kernel_shape, get_strides(onnx_node),
                          get_padding(onnx_node));

  const FlowNode *par = get_parent_nodes(onnx_node)[0];
  return flow::CreateConvLayer(flow, par, kernel, output_channel_cnt);
}

FlowNode *CreateMaxPool(Flow &flow, onnx::NodeProto &onnx_node) {
  const FlowNode *par = get_parent_nodes(onnx_node)[0];
  KernelAttributes kernel(get_ints_attribute(onnx_node, ATTR_KERNEL_SHAPE),
                          get_strides(onnx_node), get_padding(onnx_node));
  return flow::CreateMaxPool(flow, par, kernel);
}

FlowNode *CreateAveragePool(Flow &flow, onnx::NodeProto &onnx_node) {
  const FlowNode *par = get_parent_nodes(onnx_node)[0];
  KernelAttributes kernel(get_ints_attribute(onnx_node, ATTR_KERNEL_SHAPE),
                          get_strides(onnx_node), get_padding(onnx_node));
  return flow::CreateAveragePool(flow, par, kernel);
}

FlowNode *CreateGlobalAveragePool(Flow &flow, onnx::NodeProto &onnx_node) {
  const FlowNode *par = get_parent_nodes(onnx_node)[0];
  return flow::CreateGlobalAveragePool(flow, par);
}

FlowNode *CreateFullyConnected(Flow &flow, onnx::NodeProto &onnx_node) {
  std::vector<std::vector<int>> input_shapes = get_input_shapes(onnx_node);

  PANIC_IF(input_shapes.size() < 2 || input_shapes.size() > 3);
  if (input_shapes.size() == 3) {
    std::cerr << "WARNING: ignorring bias of fully connected layer "
              << onnx_node.name() << "\n";
  }
  PANIC_IF(input_shapes[0].size() != 1);
  PANIC_IF(input_shapes[1].size() != 2);
  PANIC_IF(input_shapes[0][0] != input_shapes[1][1]);
  PANIC_IF(input_shapes.size() >= 3 &&
           input_shapes[2][0] != input_shapes[1][0]);

  const FlowNode *par = get_parent_nodes(onnx_node)[0];
  return flow::CreateFullyConnected(flow, par, input_shapes[1][0]);
}

FlowNode *CreateFlatten(Flow &flow, onnx::NodeProto &onnx_node) {
  int axis = 1;
  if (attribute_exists(onnx_node, ATTR_AXIS)) {
    axis = get_attribute_int(onnx_node, ATTR_AXIS);
  }
  PANIC_IF(axis != 1, axis, "We support only flattening all axes!");

  const FlowNode *par = get_parent_nodes(onnx_node)[0];
  return flow::CreateFlatten(flow, par);
}

// Specification of ONNX operations:
// https://github.com/onnx/onnx/blob/master/docs/Operators.md
void CreateNode(Flow &flow, onnx::NodeProto &onnx_node) {
  FlowNode *new_node = nullptr;

  if (onnx_node.op_type() == "Add") {
    new_node = CreateAdd(flow, onnx_node);
  } else if (onnx_node.op_type() == "AveragePool") {
    new_node = CreateAveragePool(flow, onnx_node);
  } else if (onnx_node.op_type() == "Conv") {
    new_node = CreateConv(flow, onnx_node);
  } else if (onnx_node.op_type() == "Flatten") {
    new_node = CreateFlatten(flow, onnx_node);
  } else if (onnx_node.op_type() == "Gemm") {
    new_node = CreateFullyConnected(flow, onnx_node);
  } else if (onnx_node.op_type() == "GlobalAveragePool") {
    new_node = CreateGlobalAveragePool(flow, onnx_node);
  } else if (onnx_node.op_type() == "MaxPool") {
    new_node = CreateMaxPool(flow, onnx_node);
  } else if (onnx_node.op_type() == "Relu") {
    new_node = CreateRelu(flow, onnx_node);
  } else {
    PANIC("ONNX operation `" + onnx_node.op_type() + "' not supported!");
  }

  const std::string &output_name = onnx_node.output(0);
  shape_map[output_name] = new_node->shape();
  std::cerr << "Found " << onnx_node.op_type() << " with name " << output_name
            << " and shape " << new_node->shape() << "\n";
  flownode_map[output_name] = new_node;
}

std::unique_ptr<onnx::ModelProto> ParseModel(const std::string &filepath) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  bool file_exists = std::experimental::filesystem::exists(
      std::experimental::filesystem::path(filepath));
  PANIC_IF(!file_exists, "ONNX file does not exist!", filepath);

  std::ifstream in(filepath, std::ios::ate | std::ios::binary);
  std::streamsize size = in.tellg();
  in.seekg(0, std::ios::beg);

  std::vector<char> buffer(size);
  in.read(buffer.data(), size);
  auto model = std::make_unique<onnx::ModelProto>();
  ParseProtoFromBytes(model.get(), buffer.data(), size);

  return model;
}

void LoadInitializers(const onnx::GraphProto &graph) {
  for (auto ini : graph.initializer()) {
    std::vector<int> shape(ini.dims().begin(), ini.dims().end());
    shape_map[ini.name()] = shape;
    std::cerr << "Found initializer " << ini.name() << " with shape " << shape
              << "\n";
  }
}

void LoadInputs(const onnx::GraphProto &graph, Flow &flow) {
  for (const auto &node : graph.input()) {
    const auto &type = node.type();
    PANIC_IF(!type.has_tensor_type(), "Only tensor inputs are supported!");

    const auto &tensor_type = type.tensor_type();
    PANIC_IF(!tensor_type.has_shape(), "Input tensor with unknown shape!");

    const auto &tensor_shape = tensor_type.shape();
    std::vector<int> shape;
    for (const auto &dim : tensor_shape.dim()) {
      PANIC_IF(!dim.has_dim_value(),
               "Only numeric tensor dimensions "
               "are supported (no parameters)");
      shape.push_back(dim.dim_value());
    }
    // Drop batch size dimension
    shape.erase(shape.begin());
    shape_map[node.name()] = shape;
    std::cerr << "Found input " << node.name() << " with shape " << shape
              << "\n";
    flownode_map[node.name()] = flow::CreateInput(flow, shape);
  }
}

void LoadNodes(const onnx::GraphProto &graph, Flow &flow) {
  for (auto node : graph.node()) {
    CreateNode(flow, node);
  }
}

int main(int argc, char **argv) {
  PANIC_IF(argc != 2,
           "Please provide filepath to *.onnx file as "
           "command-line argument!");
  auto model = ParseModel(argv[1]);
  std::cout << model->has_graph() << std::endl;
  if (!model->has_graph()) {
    PANIC("Model does not have a graph!");
  }
  auto graph = model->graph();

  auto flow = OnnxGraph::MakeFlow(&graph);

  google::protobuf::ShutdownProtobufLibrary();
  janncy::Draw(*flow, "flow");
  std::cerr << "Nodes in flow: " << flow->nodes().size() << "\n";
  CtGraph ct_graph = Cipherfier::Cipherfy(*flow);

  janncy::Draw(ct_graph, "ct_graph");
  std::cerr << "Nodes in ct_graph: " << ct_graph.nodes().size() << "\n";
}
