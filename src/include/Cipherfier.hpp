#ifndef CIPHERFIER_HPP_
#define CIPHERFIER_HPP_

#include <unordered_map>

#include "CtGraph.hpp"
#include "CtTensor.hpp"
#include "Flow.hpp"
#include "FlowVisitor.hpp"
#include "KernelAttributes.hpp"

namespace janncy {

class Cipherfier : public FlowVisitor {
 public:
  static CtGraph cipherfy(Flow& flow);

  void visit(ConvLayer& node) override;
  void visit(FullyConnected& node) override;
  void visit(AveragePool& node) override;
  void visit(BatchNormalization& node) override;
  void visit(Add& node) override;
  void visit(Input& node) override;
  void visit(ReLU& node) override;
  void visit(MaxPool& node) override;
  void visit(Flatten& node) override;

 private:
  CtGraph ct_graph_;
  Flow& flow_;
  std::unordered_map<const FlowNode*, CtTensor> tensor_map_;

  Cipherfier(Flow& flow);

  const CtTensor& get_parent_tensor(const FlowNode& node) const;
  const CtTensor& get_parent_tensor(const FlowNode& node, int parent_ind) const;

  const CtOp* sum_ciphertexts(const std::vector<const CtOp*>& cts);

  // slot i of result is the sum of ct[i:i + sum_length]
  // Should also be doable with strides
  const CtOp* prefix_sums(const CtOp* ct, int sum_length);

  // return a ct consisting of the first element from each of `cts`
  // Assumes the remaining elements are all 0s
  const CtOp* flatten_slots(const std::vector<const CtOp*>& cts);
  const CtOp* apply_filter(const CtTensor& input,
                           const KernelAttributes& kernel);

  // return {ct^1, ct^2, ..., ct^degree}
  std::vector<const CtOp*> get_ct_powers(const CtOp* ct, int degree);
  const CtOp* poly_eval(const CtOp* parent, int degree);
  const CtOp* relu_polynomial(CtGraph& ct_graph, const CtOp* parent);
};

}  // namespace janncy

#endif  // CIPHERFIER_HPP_
