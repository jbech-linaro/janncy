#ifndef JANNCY_CIPHERTEXT_EVALUATOR_H_
#define JANNCY_CIPHERTEXT_EVALUATOR_H_

#include <complex>
#include <unordered_map>
#include <vector>

#include "include/ciphertext.h"
#include "include/ct_graph_visitor.h"

namespace janncy {

class CtGraph;

class CtAdd;
class CtMul;
class CtPtAdd;
class CtPtMul;
class CtRotate;
class CtInput;

class CiphertextEvaluator : public CtGraphVisitor {
 public:
  CiphertextEvaluator(std::vector<std::vector<std::complex<double> > > inputs)
      : inputs_(inputs){};

  void Visit(CtGraph* ct_graph, CtAdd* node) override;
  void Visit(CtGraph* ct_graph, CtMul* node) override;
  void Visit(CtGraph* ct_graph, CtPtAdd* node) override;
  void Visit(CtGraph* ct_graph, CtPtMul* node) override;
  void Visit(CtGraph* ct_graph, CtRotate* node) override;
  void Visit(CtGraph* ct_graph, CtInput* node) override;

  std::vector<std::vector<std::complex<double> > > result(
      CtGraph* ct_graph) const;

 private:
  std::vector<std::vector<std::complex<double> > > inputs_;
  std::unordered_map<CtOp*, Ciphertext> node_map_;
};

}  // namespace janncy

#endif  // JANNCY_CIPHERTEXT_EVALUATOR_H_
