#ifndef JANNCY_CLEARTEXT_EVALUATOR_H_
#define JANNCY_CLEARTEXT_EVALUATOR_H_

#include <unordered_map>
#include <vector>

#include "include/ct_graph_visitor.h"

namespace janncy {

class CtGraph;

class CtAdd;
class CtMul;
class CtPtAdd;
class CtPtMul;
class CtRotate;
class CtInput;

class CleartextEvaluator : public CtGraphVisitor {
 public:
  CleartextEvaluator(std::vector<std::vector<double> > inputs)
      : inputs_(inputs){};

  void visit(CtGraph* ct_graph, CtAdd* node) override;
  void visit(CtGraph* ct_graph, CtMul* node) override;
  void visit(CtGraph* ct_graph, CtPtAdd* node) override;
  void visit(CtGraph* ct_graph, CtPtMul* node) override;
  void visit(CtGraph* ct_graph, CtRotate* node) override;
  void visit(CtGraph* ct_graph, CtInput* node) override;

  std::vector<std::vector<double> > result(CtGraph* ct_graph) const;

 private:
  std::vector<std::vector<double> > inputs_;
  std::unordered_map<CtOp*, std::vector<double> > node_map_;
};

}  // namespace janncy

#endif  // JANNCY_CLEARTEXT_EVALUATOR_H_
