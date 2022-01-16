#ifndef JANNCY_CIPHERTEXT_EVALUATOR_H_
#define JANNCY_CIPHERTEXT_EVALUATOR_H_

#include <complex>
#include <unordered_map>
#include <vector>

#include "include/ciphertext.h"
#include "include/ct_graph.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

class CtAdd;
class CtMul;
class CtPtAdd;
class CtPtMul;
class CtRotate;
class CtInput;

class CiphertextEvaluator : public CtGraphVisitor {
 public:
  static std::vector<std::vector<std::complex<double>>> Evaluate(
      CtGraph& ct_graph, std::vector<std::vector<std::complex<double>>> inputs);

  void Visit(CtAdd* node) override;
  void Visit(CtMul* node) override;
  void Visit(CtPtAdd* node) override;
  void Visit(CtPtMul* node) override;
  void Visit(CtRotate* node) override;
  void Visit(CtInput* node) override;

  std::vector<std::vector<std::complex<double>>> result() const;

 private:
  CiphertextEvaluator(CtGraph& ct_graph,
                      std::vector<std::vector<std::complex<double>>> inputs);
  CtGraph& ct_graph_;
  std::vector<std::vector<std::complex<double>>> inputs_;
  std::unordered_map<CtOp*, Ciphertext> node_map_;
};

}  // namespace janncy

#endif  // JANNCY_CIPHERTEXT_EVALUATOR_H_
