#ifndef CTPTMUL_HPP_
#define CTPTMUL_HPP_

#include "CtOp.hpp"

#include <string>
#include <vector>

namespace janncy {

class CtGraphVisitor;

class CtPtMul : public CtOp {
  public:
    CtPtMul();

    std::vector<double> value() const;

    void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;

  private:
    std::vector<double> value_;
};

}  // namespace janncy

#endif  // CTPTMUL_HPP_
