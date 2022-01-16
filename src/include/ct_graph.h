#ifndef JANNCY_CT_GRAPH_H_
#define JANNCY_CT_GRAPH_H_

#include <vector>

#include "include/ct_op.h"
#include "include/graph.h"

namespace janncy {

class CtGraphVisitor;

class CtGraph : public Graph<CtOp> {
 public:
  // TODO(nsamar): Make evaluate() and cipherfy() const
  // TODO(alex): Move this evaluate directly to the visitor class?
  std::vector<std::vector<double>> Evaluate(
      std::vector<std::vector<double>> init_values);

  CtOp* CreateInput();
  CtOp* CreateAdd(const CtOp* parent_1, const CtOp* parent_2);
  CtOp* CreateMul(const CtOp* parent_1, const CtOp* parent_2);
  CtOp* CreatePtAdd(const CtOp* parent);
  CtOp* CreatePtMul(const CtOp* parent);
  CtOp* CreateRotate(const CtOp* parent);
};

}  // namespace janncy

#endif  // JANNCY_CT_GRAPH_H_
