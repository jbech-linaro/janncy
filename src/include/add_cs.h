#ifndef JANNCY_ADD_CS_H_
#define JANNCY_ADD_CS_H_

#include <vector>

#include "include/ct_op.h"
#include "include/ct_op_visitor.h"
#include "include/message.h"

namespace janncy {

class AddCS : public CtOp {
 public:
  void Accept(CtOpVisitor& visitor) const override {
    return visitor.Visit(*this);
  }
  std::string op_type() const override { return "AddCS"; }

  Message::Scalar scalar() const { return scalar_; }

 private:
  Message::Scalar scalar_;
};

}  // namespace janncy

#endif  // JANNCY_ADD_CS_H_
