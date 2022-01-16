#ifndef JANNCY_CT_ROTATE_H_
#define JANNCY_CT_ROTATE_H_

#include "include/ct_op.h"

namespace janncy {

class CtGraphVisitor;

class CtRotate : public CtOp {
 public:
  CtRotate();

  int amt() const;

  void Accept(CtGraphVisitor& visitor) override;

 private:
  int amt_;
};

}  // namespace janncy

#endif  // JANNCY_CT_ROTATE_H_
