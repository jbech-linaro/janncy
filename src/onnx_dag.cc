#include "include/onnx_dag.h"

#include "include/onnx_node.h"
#include "include/panic.h"

namespace janncy {

void OnnxDag::AddNode(std::unique_ptr<OnnxNode> onnx_node) {
  auto node_parents = OnnxNodeParents(*this, *onnx_node);
  auto& onnx_node_ref = onnx_dag_.AddNode(std::move(onnx_node), node_parents);
  output_name_map_.emplace(onnx_node_ref.output(), &onnx_node_ref);
}

const OnnxNode& OnnxDag::OutputNameToNode(
    const std::string& parent_output_name) const {
  PANIC_IF(!output_name_map_.count(parent_output_name));
  return *output_name_map_.at(parent_output_name);
}

std::vector<const OnnxNode*> OnnxNodeParents(const OnnxDag& onnx_dag,
                                             const OnnxNode& onnx_node) {
  std::vector<const OnnxNode*> result;
  result.reserve(onnx_node.inputs().size());
  for (const auto& parent_output_name : onnx_node.inputs()) {
    result.push_back(&onnx_dag.OutputNameToNode(parent_output_name));
  }
  return result;
}

OnnxDag MakeOnnxDag(OwnedOnnxNodeVec onnx_nodes) {
  OnnxDag onnx_dag;
  for (auto& onnx_node : onnx_nodes) {
    std::cout << "Adding " << onnx_node->name() << std::endl;
    onnx_dag.AddNode(std::move(onnx_node));
  }
  return onnx_dag;
}

}  // namespace janncy
