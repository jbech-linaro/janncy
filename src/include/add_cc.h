#ifndef JANNCY_ADD_CC_H_
#define JANNCY_ADD_CC_H_

#include <string>

#include "include/ct_op.h"
#include "include/ct_op_visitor.h"

namespace janncy {

class AddCC : public CtOp {
 public:
  void Accept(CtOpVisitor& visitor) const override {
    return visitor.Visit(*this);
  }
  std::string op_type() const override { return "AddCC"; }
};

}  // namespace janncy

#endif  // JANNCY_ADD_CC_H_
