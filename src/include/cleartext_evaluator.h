#ifndef JANNCY_CLEARTEXT_EVALUATOR_H_
#define JANNCY_CLEARTEXT_EVALUATOR_H_

#include <complex>
#include <unordered_map>
#include <vector>

#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

class CtAdd;
class CtMul;
class CtPtAdd;
class CtPtMul;
class CtRotate;
class CtInput;

class CleartextEvaluator : public CtGraphVisitor {
 public:
  static std::vector<std::vector<double>> Evaluate(
      CtGraph& ct_graph, std::vector<std::vector<double>> inputs);

  void Visit(CtAdd* node) override;
  void Visit(CtMul* node) override;
  void Visit(CtPtAdd* node) override;
  void Visit(CtPtMul* node) override;
  void Visit(CtRotate* node) override;
  void Visit(CtInput* node) override;

  std::vector<std::vector<double>> result() const;

 private:
  CleartextEvaluator(CtGraph& ct_graph, std::vector<std::vector<double>> inputs)
      : ct_graph_(ct_graph), inputs_(inputs){};
  CtGraph& ct_graph_;
  std::vector<std::vector<double>> inputs_;
  std::unordered_map<CtOp*, std::vector<double>> node_map_;
};

}  // namespace janncy

#endif  // JANNCY_CLEARTEXT_EVALUATOR_H_
