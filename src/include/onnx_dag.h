#ifndef JANNCY_ONNX_DAG_H_
#define JANNCY_ONNX_DAG_H_

#include <memory>
#include <unordered_map>

#include "include/dag.h"
#include "include/onnx_node.h"

namespace janncy {

class OnnxDag {
 public:
  OnnxDag() = default;
  OnnxDag(OnnxDag&&) = default;
  OnnxDag(const OnnxDag&) = delete;
  OnnxDag& operator=(const OnnxDag&) = delete;
  OnnxDag& operator=(const OnnxDag&&) = default;

  const OnnxNode& OutputNameToNode(const std::string& node_name) const;
  void AddNode(std::unique_ptr<OnnxNode> onnx_node);
  std::vector<const OnnxNode*> nodes() const { return onnx_dag_.nodes(); }

 private:
  Dag<OnnxNode> onnx_dag_;
  std::unordered_map<std::string, const OnnxNode*> output_name_map_;
};

std::vector<const OnnxNode*> OnnxNodeParents(const OnnxDag& onnx_dag,
                                             const OnnxNode& onnx_node);

OnnxDag MakeOnnxDag(OwnedOnnxNodeVec onnx_nodes);

}  // namespace janncy

#endif  // JANNCY_ONNX_DAG_H_
