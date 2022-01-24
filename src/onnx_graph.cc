#include "include/onnx_graph.h"

#include <algorithm>
#include <memory>

#include <onnx/defs/tensor_proto_util.h>
#include <onnx/onnx_pb.h>
#include <onnx/proto_utils.h>

#include "include/neural_network.h"
#include "include/panic.h"

namespace janncy {

// TODO(nsamar): All of these unordered_maps are terrible and should be
// replaced by OnnxNode private attributes with accessors or something

// TODO(nsamar): OnnxGraph should be a Graph<OnnxNode>

std::unique_ptr<NeuralNetwork> OnnxGraph::MakeNeuralNetwork(
    const onnx::GraphProto& graph_proto) {
  auto onnx_graph = OnnxGraph(graph_proto);
  onnx_graph.LoadInitializers();
  onnx_graph.LoadInputs();
  onnx_graph.LoadNodes();
  return std::move(onnx_graph.nn_);
}

OnnxGraph::OnnxGraph(const onnx::GraphProto& graph)
    : graph_(graph), nn_(std::make_unique<NeuralNetwork>()) {}

std::vector<const OnnxNode*> OnnxGraph::Parents(const OnnxNode& node) {
  std::vector<const OnnxNode*> result;
  for (auto parent_string : node.input()) {
    std::cout << "parent string: " << parent_string << std::endl;
    if (onnxnode_map_.count(parent_string)) {
      result.push_back(onnxnode_map_.at(parent_string));
    }
  }
  return result;
}

std::vector<const Layer*> OnnxGraph::LayerParents(const OnnxNode& node) {
  auto parents_vec = Parents(node);
  std::vector<const Layer*> result;
  for (auto parent : parents_vec) {
    std::cout << "New parent of " << node.name() << std::endl;
    result.push_back(layer_map_.at(parent));
  }
  return result;
}

void OnnxGraph::LoadInitializers() {
  for (auto& ini : graph_.initializer()) {
    Shape shape(ini.dims().begin(), ini.dims().end());
    shape_map_[ini.name()] = shape;
    std::cerr << "Found initializer " << ini.name() << " with shape " << shape
              << "\n";
  }
}

void OnnxGraph::LoadInputs() {
  for (const auto& node_proto : graph_.input()) {
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

    shape_map_.emplace(node_proto.name(), shape);
    std::cerr << "Found input " << node_proto.name() << " with shape " << shape
              << "\n";
    nodes_.push_back(new OnnxNode(shape));
    onnxnode_map_[node_proto.name()] = nodes_.back();
    layer_map_.emplace(nodes_.back(),
                       &neural_network::CreateInput(*nn_, shape));
  }
}

namespace {

const std::string ATTR_STRIDES = "strides";
const std::string ATTR_PADDING = "pads";
const std::string ATTR_AUTO_PAD = "auto_pad";
const std::string ATTR_KERNEL_SHAPE = "kernel_shape";
const std::string ATTR_AXIS = "axis";

const Layer& CreateRelu(NeuralNetwork& nn, const OnnxNode& onnx_node,
                        const Layer& parent) {
  return neural_network::CreateRelu(nn, parent);
}

const Layer& CreateAdd(NeuralNetwork& nn, const OnnxNode& onnx_node,
                       const Layer& parent0, const Layer& parent1) {
  return neural_network::CreateAdd(nn, parent0, parent1);
}

const Layer& CreateConv(NeuralNetwork& nn, const OnnxNode& onnx_node,
                        const Layer& parent) {
  std::vector<Shape> input_shapes = onnx_node.input_shapes();

  // Infer from weights input shape
  PANIC_IF(input_shapes.size() < 2);
  if (input_shapes.size() > 2) {
    std::cerr << "WARNING: ignoring biases of ConvLayer " << onnx_node.name()
              << "\n";
  }
  const Shape& weights_shape = input_shapes[1];
  int output_channel_cnt = weights_shape[0];
  PANIC_IF(weights_shape[1] != input_shapes[0][0],
           "ConvLayer mismatching number of channels", weights_shape,
           input_shapes[0]);

  Shape kernel_shape = weights_shape.SubShape(2);
  KernelAttributes kernel(kernel_shape, onnx_node.strides(),
                          onnx_node.padding());

  return neural_network::CreateConvLayer(nn, parent, kernel,
                                         output_channel_cnt);
}

const Layer& CreateMaxPool(NeuralNetwork& nn, const OnnxNode& onnx_node,
                           const Layer& parent) {
  return neural_network::CreateMaxPool(nn, parent,
                                       onnx_node.kernel_for_pooling());
}

const Layer& CreateAveragePool(NeuralNetwork& nn, const OnnxNode& onnx_node,
                               const Layer& parent) {
  return neural_network::CreateAveragePool(nn, parent,
                                           onnx_node.kernel_for_pooling());
}

const Layer& CreateGlobalAveragePool(NeuralNetwork& nn,
                                     const OnnxNode& onnx_node,
                                     const Layer& parent) {
  return neural_network::CreateGlobalAveragePool(nn, parent);
}

const Layer& CreateFullyConnected(NeuralNetwork& nn, const OnnxNode& onnx_node,
                                  const Layer& parent) {
  std::vector<Shape> input_shapes = onnx_node.input_shapes();

  PANIC_IF(input_shapes.size() < 2 || input_shapes.size() > 3);
  if (input_shapes.size() == 3) {
    std::cerr << "WARNING: ignorring bias of fully connected layer "
              << onnx_node.name() << "\n";
  }
  PANIC_IF(input_shapes[0].dimension_cnt() != 1);
  PANIC_IF(input_shapes[1].dimension_cnt() != 2);
  PANIC_IF(input_shapes[0][0] != input_shapes[1][1]);
  PANIC_IF(input_shapes.size() >= 3 &&
           input_shapes[2][0] != input_shapes[1][0]);

  return neural_network::CreateFullyConnected(nn, parent, input_shapes[1][0]);
}

const Layer& CreateFlatten(NeuralNetwork& nn, const OnnxNode& onnx_node,
                           const Layer& parent) {
  int axis = 1;
  if (onnx_node.AttributeExists(ATTR_AXIS)) {
    axis = onnx_node.int_attribute(ATTR_AXIS);
  }
  PANIC_IF(axis != 1, axis, "We support only flattening all axes!");

  return neural_network::CreateFlatten(nn, parent);
}

const Layer& CreateLayer(NeuralNetwork& nn, const OnnxNode& onnx_node,
                         std::vector<const Layer*> parents) {
  PANIC_IF(parents.size() < 1 || !parents[0]);
  if (onnx_node.op_type() == "Add") {
    PANIC_IF(parents.size() < 2 && !parents[1]);
    return CreateAdd(nn, onnx_node, *parents[0], *parents[1]);
  } else if (onnx_node.op_type() == "AveragePool") {
    return CreateAveragePool(nn, onnx_node, *parents[0]);
  } else if (onnx_node.op_type() == "Conv") {
    return CreateConv(nn, onnx_node, *parents[0]);
  } else if (onnx_node.op_type() == "Flatten") {
    return CreateFlatten(nn, onnx_node, *parents[0]);
  } else if (onnx_node.op_type() == "Gemm") {
    return CreateFullyConnected(nn, onnx_node, *parents[0]);
  } else if (onnx_node.op_type() == "GlobalAveragePool") {
    return CreateGlobalAveragePool(nn, onnx_node, *parents[0]);
  } else if (onnx_node.op_type() == "MaxPool") {
    return CreateMaxPool(nn, onnx_node, *parents[0]);
  } else if (onnx_node.op_type() == "Relu") {
    return CreateRelu(nn, onnx_node, *parents[0]);
  } else {
    PANIC("ONNX operation `" + onnx_node.op_type() + "' not supported!");
  }
}

}  // namespace

// Specification of ONNX operations:
// https://github.com/onnx/onnx/blob/master/docs/Operators.md
void OnnxGraph::AddLayer(const OnnxNode& onnx_node) {
  auto parents = LayerParents(onnx_node);
  std::cout << "parents size: " << parents.size() << std::endl;
  const Layer& new_flow_node = CreateLayer(*nn_, onnx_node, parents);
  const std::string output_name = onnx_node.output()[0];
  shape_map_.emplace(output_name, new_flow_node.shape());
  std::cerr << "Found " << onnx_node.op_type() << " with name " << output_name
            << " and shape " << new_flow_node.shape() << "\n";
  layer_map_.emplace(&onnx_node, &new_flow_node);
}

void OnnxGraph::LoadNodes() {
  for (auto& node_proto : graph_.node()) {
    std::vector<Shape> input_shapes;
    for (const auto& input_name : node_proto.input()) {
      input_shapes.push_back(shape_map_.at(input_name));
    }
    nodes_.push_back(new OnnxNode(node_proto, input_shapes));
    std::cout << node_proto.name() << std::endl;
    onnxnode_map_[nodes_.back()->output()[0]] = nodes_.back();
    AddLayer(*nodes_.back());
  }
}

}  // namespace janncy
