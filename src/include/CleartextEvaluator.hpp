#ifndef CLEARTEXTEVALUATOR_HPP_
#define CLEARTEXTEVALUATOR_HPP_

#include "CtGraphVisitor.hpp"

#include <unordered_map>
#include <vector>

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

#endif  // CLEARTEXTEVALUATOR_HPP_
