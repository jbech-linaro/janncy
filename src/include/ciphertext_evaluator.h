#ifndef JANNCY_CIPHERTEXT_EVALUATOR_H_
#define JANNCY_CIPHERTEXT_EVALUATOR_H_

#include <unordered_map>
#include <vector>

#include "include/ciphertext.h"
#include "include/ct_dag.h"
#include "include/ct_op_visitor.h"
#include "include/message.h"
#include "include/weight_manager.h"

namespace janncy {

class CiphertextEvaluator : public CtOpVisitor {
 public:
  static std::vector<Message::Vector> Evaluate(
      const WeightManager& weight_manager, const CtDag& ct_dag,
      std::vector<Message::Vector> inputs);

  void Visit(const AddCC& node) override;
  void Visit(const AddCP& node) override;
  void Visit(const AddCS& node) override;
  void Visit(const MulCC& node) override;
  void Visit(const MulCP& node) override;
  void Visit(const MulCS& node) override;
  void Visit(const RotateC& node) override;
  void Visit(const CtInput& node) override;

  std::vector<Message::Vector> result() const;

 private:
  CiphertextEvaluator(const WeightManager& weight_manager, const CtDag& ct_dag,
                      std::vector<Message::Vector> inputs);
  const WeightManager& weight_manager_;
  const CtDag& ct_dag_;
  std::vector<Message::Vector> inputs_;
  std::unordered_map<const CtOp*, Ciphertext> node_map_;
};

}  // namespace janncy

#endif  // JANNCY_CIPHERTEXT_EVALUATOR_H_
