#ifndef CTPTMUL_HPP_
#define CTPTMUL_HPP_

#include "CtOp.hpp"

#include <string>
#include <vector>

class CtGraphVisitor;

class CtPtMul : public CtOp {
  public:
    CtPtMul();

    std::vector<double> value() const;

    void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;

  private:
    std::vector<double> value_;
};

#endif  // CTPTMUL_HPP_
