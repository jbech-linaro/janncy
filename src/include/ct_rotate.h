#ifndef JANNCY_CT_ROTATE_H_
#define JANNCY_CT_ROTATE_H_

#include "include/ct_op.h"

namespace janncy {

class CtGraphVisitor;

class CtRotate : public CtOp {
 public:
  void Accept(CtOpVisitor& visitor) const override;
  std::string op_type() const override;

  int amt() const;

 private:
  int amt_;
};

}  // namespace janncy

#endif  // JANNCY_CT_ROTATE_H_
