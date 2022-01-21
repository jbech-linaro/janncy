#ifndef JANNCY_CIPHERFIER_H_
#define JANNCY_CIPHERFIER_H_

#include <unordered_map>

#include "include/ct_graph.h"
#include "include/ct_tensor.h"
#include "include/flow.h"
#include "include/flow_visitor.h"
#include "include/kernel_attributes.h"

namespace janncy {

class Cipherfier : public FlowVisitor {
 public:
  static CtGraph Cipherfy(const Flow& flow);

  void Visit(const ConvLayer& node) override;
  void Visit(const FullyConnected& node) override;
  void Visit(const AveragePool& node) override;
  void Visit(const BatchNormalization& node) override;
  void Visit(const Add& node) override;
  void Visit(const Input& node) override;
  void Visit(const ReLU& node) override;
  void Visit(const MaxPool& node) override;
  void Visit(const Flatten& node) override;

 private:
  CtGraph ct_graph_;
  const Flow& flow_;
  std::unordered_map<const FlowNode*, CtTensor> tensor_map_;

  Cipherfier(const Flow& flow);

  const CtTensor& get_parent_tensor(const FlowNode& node) const;
  const CtTensor& get_parent_tensor(const FlowNode& node, int parent_ind) const;
};

}  // namespace janncy

#endif  // JANNCY_CIPHERFIER_H_
