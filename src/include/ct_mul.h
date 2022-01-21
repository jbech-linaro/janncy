#ifndef JANNCY_CT_MUL_H_
#define JANNCY_CT_MUL_H_

#include <string>

#include "include/ct_op.h"

namespace janncy {

class CtGraphVisitor;

class CtMul : public CtOp {
 public:
  void Accept(CtGraphVisitor& visitor) override;
  std::string op_type() const override;
};

}  // namespace janncy

#endif  // JANNCY_CT_MUL_H_
