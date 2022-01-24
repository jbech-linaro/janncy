#ifndef JANNCY_CLEARTEXT_EVALUATOR_H_
#define JANNCY_CLEARTEXT_EVALUATOR_H_

#include <unordered_map>
#include <vector>

#include "include/ct_dag.h"
#include "include/ct_graph_visitor.h"
#include "include/message.h"

namespace janncy {

class CleartextEvaluator : public CtGraphVisitor {
 public:
  static std::vector<Message> Evaluate(const CtDag& ct_dag,
                                       std::vector<Message> inputs);

  void Visit(const CtAdd& node) override;
  void Visit(const CtMul& node) override;
  void Visit(const CtPtAdd& node) override;
  void Visit(const CtPtMul& node) override;
  void Visit(const CtRotate& node) override;
  void Visit(const CtInput& node) override;

  std::vector<Message> result() const;

 private:
  CleartextEvaluator(const CtDag& ct_dag, std::vector<Message> inputs);
  const CtDag& ct_dag_;
  std::vector<Message> inputs_;
  std::unordered_map<const CtOp*, Message> node_map_;
};

}  // namespace janncy

#endif  // JANNCY_CLEARTEXT_EVALUATOR_H_
