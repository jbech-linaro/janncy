#ifndef JANNCY_CT_MUL_H_
#define JANNCY_CT_MUL_H_

#include <string>

#include "include/ct_op.h"

namespace janncy {

class CtGraphVisitor;

class CtMul : public CtOp {
 public:
  CtMul();

  void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;
};

}  // namespace janncy

#endif  // JANNCY_CT_MUL_H_
