#ifndef CTMUL_HPP_
#define CTMUL_HPP_

#include <string>

#include "CtOp.hpp"

namespace janncy {

class CtGraphVisitor;

class CtMul : public CtOp {
 public:
  CtMul();

  void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;
};

}  // namespace janncy

#endif  // CTMUL_HPP_
