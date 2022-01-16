#ifndef JANNCY_CT_PT_ADD_H_
#define JANNCY_CT_PT_ADD_H_

#include <vector>

#include "include/ct_op.h"

namespace janncy {

class CtGraphVisitor;

class CtPtAdd : public CtOp {
 public:
  CtPtAdd();

  std::vector<double> value() const;

  void Accept(CtGraphVisitor& visitor) override;

 private:
  std::vector<double> value_;
};

}  // namespace janncy

#endif  // JANNCY_CT_PT_ADD_H_
