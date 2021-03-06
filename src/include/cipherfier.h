#ifndef JANNCY_CIPHERFIER_H_
#define JANNCY_CIPHERFIER_H_

#include <unordered_map>

#include "include/ct_dag.h"
#include "include/ct_tensor.h"
#include "include/kernel_attributes.h"
#include "include/layer_visitor.h"
#include "include/neural_network.h"

namespace janncy {

class Cipherfier : public LayerVisitor {
 public:
  static CtDag Cipherfy(const NeuralNetwork& nn);

  void Visit(const ConvLayer& node) override;
  void Visit(const FullyConnectedLayer& node) override;
  void Visit(const AveragePoolLayer& node) override;
  void Visit(const BatchNormalizationLayer& node) override;
  void Visit(const AddLayer& node) override;
  void Visit(const InputLayer& node) override;
  void Visit(const ReluLayer& node) override;
  void Visit(const MaxPoolLayer& node) override;
  void Visit(const FlattenLayer& node) override;

 private:
  CtDag ct_dag_;
  const NeuralNetwork& nn_;
  std::unordered_map<const Layer*, CtTensor> tensor_map_;

  Cipherfier(const NeuralNetwork& nn);

  const CtTensor& get_parent_tensor(const Layer& node) const;
  const CtTensor& get_parent_tensor(const Layer& node, int parent_ind) const;
};

}  // namespace janncy

#endif  // JANNCY_CIPHERFIER_H_
