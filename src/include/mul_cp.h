#ifndef JANNCY_MUL_CP_H_
#define JANNCY_MUL_CP_H_

#include <vector>

#include "include/ct_op.h"
#include "include/message.h"

namespace janncy {

class CtGraphVisitor;

class MulCP : public CtOp {
 public:
  void Accept(CtOpVisitor& visitor) const override {
    return visitor.Visit(*this);
  }
  std::string op_type() const override { return "MulCP"; }

  Message* message() const { return message_.get(); }

 private:
  std::unique_ptr<Message> message_;
};

}  // namespace janncy

#endif  // JANNCY_MUL_CP_H_
