#ifndef JANNCY_MUL_CS_H_
#define JANNCY_MUL_CS_H_

#include <memory>
#include <vector>

#include "include/ct_op.h"
#include "include/message.h"

namespace janncy {

class CtOpVisitor;

class MulCS : public CtOp {
 public:
  void Accept(CtOpVisitor& visitor) const override {
    return visitor.Visit(*this);
  }
  std::string op_type() const override { return "MulCS"; }

  Message::Scalar scalar() const { return scalar_; }

 private:
  Message::Scalar scalar_;
};

}  // namespace janncy

#endif  // JANNCY_MUL_CS_H_
