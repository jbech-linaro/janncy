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
  CleartextEvaluator(CtGraph& ct_graph, std::vector<Message> inputs)
      : ct_graph_(ct_graph), inputs_(inputs){};
  CtGraph& ct_graph_;
  std::vector<Message> inputs_;
  std::unordered_map<CtOp*, Message> node_map_;
};

}  // namespace janncy

#endif  // JANNCY_CLEARTEXT_EVALUATOR_H_
