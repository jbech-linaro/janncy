#ifndef CLEARTEXTEVALUATOR_HPP_
#define CLEARTEXTEVALUATOR_HPP_

#include "CtGraphVisitor.hpp"

#include <unordered_map>
#include <vector>

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

    void visit(CtAdd* node) override;
    void visit(CtMul* node) override;
    void visit(CtPtAdd* node) override;
    void visit(CtPtMul* node) override;
    void visit(CtRotate* node) override;
    void visit(CtInput* node) override;

    std::vector<std::vector<double> > result() const;

  private:
    std::vector<std::vector<double> > inputs_;
    std::unordered_map<CtOp*, std::vector<double> > node_map_;
};

#endif  // CLEARTEXTEVALUATOR_HPP_
