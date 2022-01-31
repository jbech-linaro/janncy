#ifndef CT_CONST_ADD_H_
#define CT_CONST_ADD_H_

#include <vector>

#include "include/ct_op.h"

namespace janncy {

class CtConstAdd : public CtOp {
 public:
  void Accept(CtOpVisitor& visitor) const override;
  std::string op_type() const override;

  ValueName value() const { return value_; }

 private:
  ValueName value_;
};

}  // namespace janncy

#endif CT_CONST_ADD_H_
