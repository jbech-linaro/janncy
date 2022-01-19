#ifndef JANNCY_CIPHERTEXT_EVALUATOR_H_
#define JANNCY_CIPHERTEXT_EVALUATOR_H_

#include <unordered_map>
#include <vector>

#include "include/ciphertext.h"
#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

class CiphertextEvaluator : public CtGraphVisitor {
 public:
  static std::vector<Message> Evaluate(CtGraph& ct_graph,
                                       std::vector<Message> inputs);

  void Visit(CtAdd& node) override;
  void Visit(CtMul& node) override;
  void Visit(CtPtAdd& node) override;
  void Visit(CtPtMul& node) override;
  void Visit(CtRotate& node) override;
  void Visit(CtInput& node) override;

  std::vector<Message> result() const;

 private:
  CiphertextEvaluator(CtGraph& ct_graph, std::vector<Message> inputs);
  CtGraph& ct_graph_;
  std::vector<Message> inputs_;
  std::unordered_map<CtOp*, Ciphertext> node_map_;
};

}  // namespace janncy

#endif  // JANNCY_CIPHERTEXT_EVALUATOR_H_
