#ifndef CTMUL_HPP_
#define CTMUL_HPP_

#include "CtOp.hpp"

#include <string>

class CtGraphVisitor;

class CtMul : public CtOp {
  public:
    CtMul();

    void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;
};

#endif  // CTMUL_HPP_
