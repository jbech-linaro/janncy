#include "include/onnx_dag_converter.h"

#include "include/neural_network.h"
#include "include/onnx_node.h"

namespace janncy {

NeuralNetwork OnnxDagConverter::TranslateOnnxDag(const OnnxDag& onnx_dag) {
  OnnxDagConverter odg(onnx_dag);
  for (const OnnxNode* node : onnx_dag.nodes()) {
    node->Accept(odg);
  }
  return std::move(odg.nn_);
}

OnnxDagConverter::OnnxDagConverter(const OnnxDag& onnx_dag)
    : onnx_dag_(onnx_dag) {}

void OnnxDagConverter::Visit(const OnnxNode& onnx_node) {}

void OnnxDagConverter::Visit(const OnnxConvLayer& onnx_node) {
  Shape weights_shape = dynamic_cast<const OnnxInitializer&>(
                            onnx_dag_.OutputNameToNode(onnx_node.W()))
                            .shape();
  auto output_channel_count = weights_shape[0];
  KernelAttributes kernel_attributes(weights_shape.SubShape(2),
                                     onnx_node.strides(), onnx_node.padding());
  auto& new_layer =
      neural_network::CreateConvLayer(nn_, *layer_map_.at(onnx_node.X()),
                                      kernel_attributes, output_channel_count);
  layer_map_.emplace(onnx_node.output(), &new_layer);
}

void OnnxDagConverter::Visit(const OnnxFullyConnectedLayer& onnx_node) {
  Shape weight_shape = dynamic_cast<const OnnxInitializer&>(
                           onnx_dag_.OutputNameToNode(onnx_node.W()))
                           .shape();
  auto& new_layer = neural_network::CreateFullyConnected(
      nn_, *layer_map_.at(onnx_node.X()), weight_shape[0]);
  layer_map_.emplace(onnx_node.output(), &new_layer);
}
void OnnxDagConverter::Visit(const OnnxAveragePoolLayer& onnx_node) {
  auto& new_layer = neural_network::CreateAveragePool(
      nn_, *layer_map_.at(onnx_node.X()), onnx_node.kernel_attributes());
  layer_map_.emplace(onnx_node.output(), &new_layer);
}

void OnnxDagConverter::Visit(const OnnxGlobalAveragePoolLayer& onnx_node) {
  auto& new_layer = neural_network::CreateGlobalAveragePool(
      nn_, *layer_map_.at(onnx_node.X()));
  layer_map_.emplace(onnx_node.output(), &new_layer);
}

void OnnxDagConverter::Visit(const OnnxBatchNormalizationLayer& onnx_node) {
  auto& new_layer = neural_network::CreateBatchNormalization(
      nn_, *layer_map_.at(onnx_node.X()));
  layer_map_.emplace(onnx_node.output(), &new_layer);
}
void OnnxDagConverter::Visit(const OnnxAddLayer& onnx_node) {
  auto& new_layer = neural_network::CreateAdd(
      nn_, *layer_map_.at(onnx_node.A()), *layer_map_.at(onnx_node.B()));
  layer_map_.emplace(onnx_node.output(), &new_layer);
}

void OnnxDagConverter::Visit(const OnnxInput& onnx_node) {
  auto& new_layer = neural_network::CreateInput(nn_, onnx_node.shape());
  layer_map_.emplace(onnx_node.output(), &new_layer);
}

void OnnxDagConverter::Visit(const OnnxReluLayer& onnx_node) {
  auto& new_layer =
      neural_network::CreateRelu(nn_, *layer_map_.at(onnx_node.X()));
  layer_map_.emplace(onnx_node.output(), &new_layer);
}

void OnnxDagConverter::Visit(const OnnxMaxPoolLayer& onnx_node) {
  auto& new_layer = neural_network::CreateMaxPool(
      nn_, *layer_map_.at(onnx_node.X()), onnx_node.kernel_attributes());
  layer_map_.emplace(onnx_node.output(), &new_layer);
}

void OnnxDagConverter::Visit(const OnnxFlattenLayer& onnx_node) {
  auto& new_layer =
      neural_network::CreateFlatten(nn_, *layer_map_.at(onnx_node.X()));
  layer_map_.emplace(onnx_node.output(), &new_layer);
}

}  // namespace janncy
