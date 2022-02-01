#ifndef JANNCY_MUL_CC_H_
#define JANNCY_MUL_CC_H_

#include <string>

#include "include/ct_op.h"

namespace janncy {

class CtOpVisitor;

class MulCC : public CtOp {
 public:
  void Accept(CtOpVisitor& visitor) const override {
    return visitor.Visit(*this);
  }
  std::string op_type() const override { return "MulCC"; }
};

}  // namespace janncy

#endif  // JANNCY_MUL_CC_H_
