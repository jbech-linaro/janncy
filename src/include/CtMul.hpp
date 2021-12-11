#ifndef CTMUL_HPP_
#define CTMUL_HPP_

#include "CtOp.hpp"

#include <string>

class CtGraphVisitor;

class CtMul : public CtOp {
  public:
    static CtMul* create(CtOp* parent0, CtOp* parent1) {
        return new CtMul(parent0, parent1);
    }
    std::string type_str() const override { return "CtMul"; }
    void visit(CtGraphVisitor* visitor) override;

  private:
    CtMul(CtOp* parent0, CtOp* parent1) : CtOp({parent0, parent1}){};
};

#endif  // CTMUL_HPP_
