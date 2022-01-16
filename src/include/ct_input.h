#ifndef JANNCY_CT_INPUT_H_
#define JANNCY_CT_INPUT_H_

#include <string>
#include <vector>

#include "include/ct_op.h"

namespace janncy {

class CtGraphVisitor;
template <class T>
class Graph;

class CtInput : public CtOp {
 public:
  CtInput();

  void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;
};

}  // namespace janncy

#endif  // JANNCY_CT_INPUT_H_
