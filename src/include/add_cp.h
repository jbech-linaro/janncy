#ifndef JANNCY_ADD_CP_H_
#define JANNCY_ADD_CP_H_

#include <memory>
#include <vector>

#include "include/ct_op.h"
#include "include/message.h"

namespace janncy {

class CtOpVisitor;

class AddCP : public CtOp {
 public:
  void Accept(CtOpVisitor& visitor) const override {
    return visitor.Visit(*this);
  }
  std::string op_type() const override { return "AddCP"; }

  Message* message() const { return message_.get(); }

 private:
  std::unique_ptr<Message> message_;
};

}  // namespace janncy

#endif  // JANNCY_ADD_CP_H_
