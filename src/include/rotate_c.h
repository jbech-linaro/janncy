#ifndef JANNCY_ROTATE_C_H_
#define JANNCY_ROTATE_C_H_

#include "include/ct_op.h"

namespace janncy {

class CtGraphVisitor;

class RotateC : public CtOp {
 public:
  void Accept(CtOpVisitor& visitor) const override {
    return visitor.Visit(*this);
  }
  std::string op_type() const override { return "RotateC"; }

  int amt() const { return amt_; }

 private:
  int amt_;
};

}  // namespace janncy

#endif  // JANNCY_ROTATE_C_H_
