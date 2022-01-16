#ifndef JANNCY_CT_ADD_H_
#define JANNCY_CT_ADD_H_

#include <string>

#include "include/ct_op.h"

namespace janncy {

class CtGraphVisitor;

class CtAdd : public CtOp {
 public:
  CtAdd();

  void Visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;

 private:
};

}  // namespace janncy

#endif  // JANNCY_CT_ADD_H_
