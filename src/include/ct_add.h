#ifndef JANNCY_CT_ADD_H_
#define JANNCY_CT_ADD_H_

#include <string>

#include "include/ct_op.h"

namespace janncy {

class CtOpVisitor;

class CtAdd : public CtOp {
 public:
  void Accept(CtOpVisitor& visitor) const override;
  std::string op_type() const override;
};

}  // namespace janncy

#endif  // JANNCY_CT_ADD_H_
