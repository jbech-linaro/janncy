#ifndef JANNCY_CT_PT_ADD_H_
#define JANNCY_CT_PT_ADD_H_

#include <vector>

#include "include/ct_op.h"

namespace janncy {

class CtOpVisitor;

class CtPtAdd : public CtOp {
 public:
  void Accept(CtOpVisitor& visitor) const override;
  std::string op_type() const override;

  ValueName value() const { return value_; }

 private:
  ValueName value_;
};

}  // namespace janncy

#endif  // JANNCY_CT_PT_ADD_H_
