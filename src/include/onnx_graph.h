#ifndef JANNCY_ONNX_GRAPH_H_
#define JANNCY_ONNX_GRAPH_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <onnx/defs/tensor_proto_util.h>
#include <onnx/onnx_pb.h>
#include <onnx/proto_utils.h>

#include "include/flow.h"
#include "include/onnx_node.h"
#include "include/shape.h"

namespace janncy {

class FlowNode;

class OnnxGraph {
 public:
  static std::unique_ptr<Flow> MakeFlow(const onnx::GraphProto& graph_proto);

 private:
  explicit OnnxGraph(const onnx::GraphProto& graph);
  std::vector<const OnnxNode*> Parents(const OnnxNode& node);
  std::vector<const FlowNode*> FlownodeParents(const OnnxNode& node);
  void LoadInitializers();
  void LoadNodes();
  void LoadInputs();
  void AddFlowNode(const OnnxNode& onnx_node);

  const onnx::GraphProto& graph_;
  std::unique_ptr<Flow> flow_;
  std::vector<OnnxNode*> nodes_;
  std::unordered_map<std::string, const OnnxNode*> onnxnode_map_;
  std::unordered_map<const OnnxNode*, const FlowNode*> flownode_map_;
  std::unordered_map<std::string, Shape> shape_map_;
};

}  // namespace janncy

#endif  // JANNCY_ONNX_GRAPH_H_
