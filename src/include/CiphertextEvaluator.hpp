#ifndef CIPHERTEXTEVALUATOR_HPP_
#define CIPHERTEXTEVALUATOR_HPP_

#include "CtGraphVisitor.hpp"

#include <unordered_map>
#include <vector>
#include <complex>

#include "include/Ciphertext.hpp"

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

    void visit(CtGraph* ct_graph, CtAdd* node) override;
    void visit(CtGraph* ct_graph, CtMul* node) override;
    void visit(CtGraph* ct_graph, CtPtAdd* node) override;
    void visit(CtGraph* ct_graph, CtPtMul* node) override;
    void visit(CtGraph* ct_graph, CtRotate* node) override;
    void visit(CtGraph* ct_graph, CtInput* node) override;

    std::vector<std::vector<std::complex<double> > > result(CtGraph* ct_graph) const;

  private:
    std::vector<std::vector<std::complex<double> > > inputs_;
    std::unordered_map<CtOp*, Ciphertext > node_map_;
};

}  // namespace janncy

#endif  // CIPHERTEXTEVALUATOR_HPP_
