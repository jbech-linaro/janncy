#ifndef JANNCY_ONNX_GRAPH_H_
#define JANNCY_ONNX_GRAPH_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <onnx/defs/tensor_proto_util.h>
#include <onnx/onnx_pb.h>
#include <onnx/proto_utils.h>

#include "include/neural_network.h"
#include "include/onnx_node.h"
#include "include/shape.h"

namespace janncy {

class Layer;

class OnnxGraph {
 public:
  static std::unique_ptr<NeuralNetwork> MakeNeuralNetwork(
      const onnx::GraphProto& graph_proto);

 private:
  explicit OnnxGraph(const onnx::GraphProto& graph);
  std::vector<const OnnxNode*> Parents(const OnnxNode& node);
  std::vector<const Layer*> LayerParents(const OnnxNode& node);
  void LoadInitializers();
  void LoadNodes();
  void LoadInputs();
  void AddLayer(const OnnxNode& onnx_node);

  const onnx::GraphProto& graph_;
  std::unique_ptr<NeuralNetwork> nn_;
  std::vector<OnnxNode*> nodes_;
  std::unordered_map<std::string, const OnnxNode*> onnxnode_map_;
  std::unordered_map<const OnnxNode*, const Layer*> layer_map_;
  std::unordered_map<std::string, Shape> shape_map_;
};

}  // namespace janncy

#endif  // JANNCY_ONNX_GRAPH_H_
