#include "include/onnx_graph.h"

#include <algorithm>
#include <memory>

#include <onnx/defs/tensor_proto_util.h>
#include <onnx/onnx_pb.h>
#include <onnx/proto_utils.h>

#include "include/flow.h"
#include "include/panic.h"

namespace janncy {

// TODO(nsamar): All of these unordered_maps are terrible and should be
// replaced by OnnxNode private attributes with accessors or something

std::unique_ptr<Flow> OnnxGraph::MakeFlow(onnx::GraphProto* graph_proto) {
  auto onnx_graph = OnnxGraph(graph_proto);
  onnx_graph.LoadInitializers();
  onnx_graph.LoadInputs();
  onnx_graph.LoadNodes();
  return std::move(onnx_graph.flow_);
}

OnnxGraph::OnnxGraph(onnx::GraphProto* graph)
    : graph_(graph), flow_(std::make_unique<Flow>()) {}

std::vector<OnnxNode*> OnnxGraph::Parents(const OnnxNode* node) {
  std::vector<OnnxNode*> result;
  for (auto parent_string : node->input()) {
    std::cout << "parent string: " << parent_string << std::endl;
    if (onnxnode_map_.count(parent_string)) {
      result.push_back(onnxnode_map_.at(parent_string));
    }
  }
  return result;
}

std::vector<const FlowNode*> OnnxGraph::FlownodeParents(const OnnxNode* node) {
  auto parents_vec = Parents(node);
  std::vector<const FlowNode*> result;
  for (auto parent : parents_vec) {
    std::cout << "New parent of " << node->name() << std::endl;
    result.push_back(flownode_map_.at(parent));
  }
  return result;
}

void OnnxGraph::LoadInitializers() {
  for (auto& ini : graph_->initializer()) {
    std::vector<int> shape(ini.dims().begin(), ini.dims().end());
    shape_map_[ini.name()] = shape;
    std::cerr << "Found initializer " << ini.name() << " with shape " << shape
              << "\n";
  }
}

void OnnxGraph::LoadInputs() {
  for (const auto& node_proto : graph_->input()) {
    const auto& type = node_proto.type();
    PANIC_IF(!type.has_tensor_type(), "Only tensor inputs are supported!");

    const auto& tensor_type = type.tensor_type();
    PANIC_IF(!tensor_type.has_shape(), "Input tensor with unknown shape!");

    const auto& tensor_shape = tensor_type.shape();
    std::vector<int> shape;
    for (const auto& dim : tensor_shape.dim()) {
      PANIC_IF(!dim.has_dim_value(),
               "Only numeric tensor dimensions "
               "are supported (no parameters)");
      shape.push_back(dim.dim_value());
    }
    // Drop batch size dimension
    shape.erase(shape.begin());
    shape_map_[node_proto.name()] = shape;
    std::cerr << "Found input " << node_proto.name() << " with shape " << shape
              << "\n";
    nodes_.push_back(new OnnxNode(shape));
    onnxnode_map_[node_proto.name()] = nodes_.back();
    flownode_map_.emplace(
        nodes_.back(), const_cast<FlowNode*>(flow::CreateInput(*flow_, shape)));
  }
}

namespace {

const std::string ATTR_STRIDES = "strides";
const std::string ATTR_PADDING = "pads";
const std::string ATTR_AUTO_PAD = "auto_pad";
const std::string ATTR_KERNEL_SHAPE = "kernel_shape";
const std::string ATTR_AXIS = "axis";

const FlowNode* CreateRelu(Flow& flow, const OnnxNode& onnx_node,
                           std::vector<const FlowNode*> parents) {
  PANIC_IF(parents.size() != 1);
  return flow::CreateRelu(flow, parents[0]);
}

const FlowNode* CreateAdd(Flow& flow, const OnnxNode& onnx_node,
                          std::vector<const FlowNode*> parents) {
  PANIC_IF(parents.size() != 2);
  return flow::CreateAdd(flow, parents);
}

const FlowNode* CreateConv(Flow& flow, const OnnxNode& onnx_node,
                           std::vector<const FlowNode*> parents) {
  PANIC_IF(parents.size() != 1);
  std::vector<std::vector<int>> input_shapes = onnx_node.input_shapes();

  // Infer from weights input shape
  PANIC_IF(input_shapes.size() < 2);
  std::vector<int> raw_kernel_shape = input_shapes[1];
  int output_channel_cnt = raw_kernel_shape[0];
  PANIC_IF(raw_kernel_shape[1] != input_shapes[0][0]);

  std::vector<int> spatial_kernel_shape(raw_kernel_shape.begin() + 2,
                                        raw_kernel_shape.end());
  KernelAttributes kernel(spatial_kernel_shape, onnx_node.strides(),
                          onnx_node.padding());

  return flow::CreateConvLayer(flow, parents[0], kernel, output_channel_cnt);
}

const FlowNode* CreateMaxPool(Flow& flow, const OnnxNode& onnx_node,
                              std::vector<const FlowNode*> parents) {
  PANIC_IF(parents.size() != 1);
  KernelAttributes kernel(onnx_node.ints_attribute(ATTR_KERNEL_SHAPE),
                          onnx_node.strides(), onnx_node.padding());
  return flow::CreateMaxPool(flow, parents[0], kernel);
}

const FlowNode* CreateAveragePool(Flow& flow, const OnnxNode& onnx_node,
                                  std::vector<const FlowNode*> parents) {
  PANIC_IF(parents.size() != 1);
  KernelAttributes kernel(onnx_node.ints_attribute(ATTR_KERNEL_SHAPE),
                          onnx_node.strides(), onnx_node.padding());
  return flow::CreateAveragePool(flow, parents[0], kernel);
}

const FlowNode* CreateGlobalAveragePool(Flow& flow, const OnnxNode& onnx_node,
                                        std::vector<const FlowNode*> parents) {
  return flow::CreateGlobalAveragePool(flow, parents[0]);
}

const FlowNode* CreateFullyConnected(Flow& flow, const OnnxNode& onnx_node,
                                     std::vector<const FlowNode*> parents) {
  PANIC_IF(parents.size() != 1);
  std::vector<std::vector<int>> input_shapes = onnx_node.input_shapes();

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

  return flow::CreateFullyConnected(flow, parents[0], input_shapes[1][0]);
}

const FlowNode* CreateFlatten(Flow& flow, const OnnxNode& onnx_node,
                              std::vector<const FlowNode*> parents) {
  PANIC_IF(parents.size() != 1);
  int axis = 1;
  if (onnx_node.AttributeExists(ATTR_AXIS)) {
    axis = onnx_node.int_attribute(ATTR_AXIS);
  }
  PANIC_IF(axis != 1, axis, "We support only flattening all axes!");

  return flow::CreateFlatten(flow, parents[0]);
}

const FlowNode* CreateFlowNode(Flow& flow, const OnnxNode& onnx_node,
                               std::vector<const FlowNode*> parents) {
  if (onnx_node.op_type() == "Add") {
    return CreateAdd(flow, onnx_node, parents);
  } else if (onnx_node.op_type() == "AveragePool") {
    return CreateAveragePool(flow, onnx_node, parents);
  } else if (onnx_node.op_type() == "Conv") {
    return CreateConv(flow, onnx_node, parents);
  } else if (onnx_node.op_type() == "Flatten") {
    return CreateFlatten(flow, onnx_node, parents);
  } else if (onnx_node.op_type() == "Gemm") {
    return CreateFullyConnected(flow, onnx_node, parents);
  } else if (onnx_node.op_type() == "GlobalAveragePool") {
    return CreateGlobalAveragePool(flow, onnx_node, parents);
  } else if (onnx_node.op_type() == "MaxPool") {
    return CreateMaxPool(flow, onnx_node, parents);
  } else if (onnx_node.op_type() == "Relu") {
    return CreateRelu(flow, onnx_node, parents);
  } else {
    PANIC("ONNX operation `" + onnx_node.op_type() + "' not supported!");
  }
}

}  // namespace

// Specification of ONNX operations:
// https://github.com/onnx/onnx/blob/master/docs/Operators.md
void OnnxGraph::AddFlowNode(const OnnxNode* onnx_node) {
  auto parents = FlownodeParents(onnx_node);
  std::cout << "parents size: " << parents.size() << std::endl;
  auto new_flow_node = CreateFlowNode(*flow_, *onnx_node, parents);
  const std::string output_name = onnx_node->output()[0];
  shape_map_.emplace(output_name, new_flow_node->shape());
  std::cerr << "Found " << onnx_node->op_type() << " with name " << output_name
            << " and shape " << new_flow_node->shape() << "\n";
  flownode_map_.emplace(onnx_node, const_cast<FlowNode*>(new_flow_node));
}

void OnnxGraph::LoadNodes() {
  for (auto& node_proto : graph_->node()) {
    std::vector<std::vector<int>> input_shapes;
    for (const auto& input_name : node_proto.input()) {
      input_shapes.push_back(shape_map_.at(input_name));
    }
    nodes_.push_back(new OnnxNode(&node_proto, input_shapes));
    std::cout << node_proto.name() << std::endl;
    onnxnode_map_[nodes_.back()->output()[0]] = nodes_.back();
    AddFlowNode(nodes_.back());
  }
}

}  // namespace janncy
