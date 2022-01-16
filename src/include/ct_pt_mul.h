#ifndef JANNCY_CT_PT_MUL_H_
#define JANNCY_CT_PT_MUL_H_

#include <vector>

#include "include/ct_op.h"

namespace janncy {

class CtGraphVisitor;

class CtPtMul : public CtOp {
 public:
  CtPtMul();

  std::vector<double> value() const;

  void Accept(CtGraphVisitor& visitor) override;

 private:
  std::vector<double> value_;
};

}  // namespace janncy

#endif  // JANNCY_CT_PT_MUL_H_
