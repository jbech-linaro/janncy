#ifndef JANNCY_CT_INPUT_H_
#define JANNCY_CT_INPUT_H_

#include <string>
#include <vector>

#include "include/ct_op.h"

namespace janncy {

class CtGraphVisitor;

class CtInput : public CtOp {
 public:
  void Accept(CtGraphVisitor& visitor) const override;
  std::string op_type() const override;
};

}  // namespace janncy

#endif  // JANNCY_CT_INPUT_H_
