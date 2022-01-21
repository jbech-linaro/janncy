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

  const CtOp* SumCiphertexts(const std::vector<const CtOp*>& cts);

  // slot i of result is the sum of ct[i:i + sum_length]
  // Should also be doable with strides
  const CtOp* PrefixSums(const CtOp* ct, int sum_length);

  // return a ct consisting of the first element from each of `cts`
  // Assumes the remaining elements are all 0s
  const CtOp* FlattenSlots(const std::vector<const CtOp*>& cts);
  const CtOp* ApplyFilter(const CtTensor& input,
                          const KernelAttributes& kernel);

  // return {ct^1, ct^2, ..., ct^degree}
  std::vector<const CtOp*> CtPowers(const CtOp* ct, int degree);
  const CtOp* PolyEval(const CtOp* parent, int degree);
  const CtOp* ReluPolynomial(CtGraph& ct_graph, const CtOp* parent);
};

}  // namespace janncy

#endif  // JANNCY_CIPHERFIER_H_
