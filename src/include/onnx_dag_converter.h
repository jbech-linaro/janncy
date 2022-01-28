#ifndef JANNCY_ONNX_DAG_CONVERTER_H_
#define JANNCY_ONNX_DAG_CONVERTER_H_

#include <unordered_map>

#include "include/neural_network.h"
#include "include/onnx_dag.h"

namespace janncy {

class OnnxNode;
class OnnxConvLayer;
class OnnxFullyConnectedLayer;
class OnnxAveragePoolLayer;
class OnnxGlobalAveragePoolLayer;
class OnnxBatchNormalizationLayer;
class OnnxAddLayer;
class OnnxInput;
class ONnxReluLayer;
class OnnxMaxPollLayer;
class OnnxFlattenLayer;

class OnnxDagConverter : public OnnxNodeVisitor {
 public:
  static NeuralNetwork TranslateOnnxDag(const OnnxDag& onnx_dag);

  void Visit(const OnnxNode& onnx_node) override;
  void Visit(const OnnxConvLayer& onnx_node) override;
  void Visit(const OnnxFullyConnectedLayer& onnx_node) override;
  void Visit(const OnnxAveragePoolLayer& onnx_node) override;
  void Visit(const OnnxGlobalAveragePoolLayer& onnx_node) override;
  void Visit(const OnnxBatchNormalizationLayer& onnx_node) override;
  void Visit(const OnnxAddLayer& onnx_node) override;
  void Visit(const OnnxInput& onnx_node) override;
  void Visit(const OnnxReluLayer& onnx_node) override;
  void Visit(const OnnxMaxPoolLayer& onnx_node) override;
  void Visit(const OnnxFlattenLayer& onnx_node) override;

 private:
  NeuralNetwork nn_;
  const OnnxDag& onnx_dag_;
  std::unordered_map<OnnxNodeId, const Layer*> layer_map_;

  OnnxDagConverter(const OnnxDag& onnx_dag);
};

}  // namespace janncy

#endif  // JANNCY_ONNX_DAG_CONVERTER_H_
