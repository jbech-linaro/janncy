#ifndef JANNCY_CT_PT_ADD_H_
#define JANNCY_CT_PT_ADD_H_

#include <string>
#include <vector>

#include "include/ct_op.h"

namespace janncy {

class CtGraphVisitor;

class CtPtAdd : public CtOp {
 public:
  CtPtAdd();

  std::vector<double> value() const;

  void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;

 private:
  std::vector<double> value_;
};

}  // namespace janncy

#endif  // JANNCY_CT_PT_ADD_H_
