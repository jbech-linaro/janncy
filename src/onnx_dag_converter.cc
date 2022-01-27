#include "include/onnx_dag_converter.h"

#include "include/onnx_node.h"

namespace janncy {

NeuralNetwork OnnxDagConverter::TranslateOnnxDag(const OnnxDag& onnx_dag) {
  OnnxDagConverter odg(onnx_dag);
  for (const auto& node : onnx_dag.nodes()) {
    node->Accept(odg);
  }
  return std::move(odg.nn_);
}

OnnxDagConverter::OnnxDagConverter(const OnnxDag& onnx_dag)
    : onnx_dag_(onnx_dag) {
  (void)onnx_dag_;
}

void OnnxDagConverter::Visit(const OnnxNode& onnx_node) {}
void OnnxDagConverter::Visit(const OnnxConvLayer& onnx_node) {}
void OnnxDagConverter::Visit(const OnnxFullyConnectedLayer& onnx_node) {}
void OnnxDagConverter::Visit(const OnnxAveragePoolLayer& onnx_node) {}
void OnnxDagConverter::Visit(const OnnxGlobalAveragePoolLayer& onnx_node) {}
void OnnxDagConverter::Visit(const OnnxBatchNormalizationLayer& onnx_node) {}
void OnnxDagConverter::Visit(const OnnxAddLayer& onnx_node) {}
void OnnxDagConverter::Visit(const OnnxInputLayer& onnx_node) {}
void OnnxDagConverter::Visit(const OnnxReluLayer& onnx_node) {}
void OnnxDagConverter::Visit(const OnnxMaxPoolLayer& onnx_node) {}

void OnnxDagConverter::Visit(const OnnxFlattenLayer& onnx_node) {}

}  // namespace janncy
