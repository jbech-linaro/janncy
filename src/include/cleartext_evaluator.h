#ifndef JANNCY_CLEARTEXT_EVALUATOR_H_
#define JANNCY_CLEARTEXT_EVALUATOR_H_

#include <unordered_map>
#include <vector>

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"
#include "include/message.h"

namespace janncy {

class CleartextEvaluator : public CtGraphVisitor {
 public:
  static std::vector<Message> Evaluate(const CtGraph& ct_graph,
                                       std::vector<Message> inputs);

  void Visit(const CtAdd& node) override;
  void Visit(const CtMul& node) override;
  void Visit(const CtPtAdd& node) override;
  void Visit(const CtPtMul& node) override;
  void Visit(const CtRotate& node) override;
  void Visit(const CtInput& node) override;

  std::vector<Message> result() const;

 private:
  CleartextEvaluator(const CtGraph& ct_graph, std::vector<Message> inputs);
  const CtGraph& ct_graph_;
  std::vector<Message> inputs_;
  std::unordered_map<const CtOp*, Message> node_map_;
};

}  // namespace janncy

#endif  // JANNCY_CLEARTEXT_EVALUATOR_H_
