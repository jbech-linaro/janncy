#ifndef JANNCY_CT_OP_H_
#define JANNCY_CT_OP_H_

#include <ostream>
#include <string>
#include <vector>

namespace janncy {

class CtOpVisitor;

class CtOp {
 public:
  CtOp() = default;
  CtOp(CtOp&&) = default;
  virtual ~CtOp() {}
  CtOp(const CtOp&) = delete;
  CtOp& operator=(const CtOp&) = delete;
  CtOp& operator=(CtOp&&) = default;

  virtual void Accept(CtOpVisitor& visitor) const = 0;
  virtual std::string op_type() const = 0;
};

std::ostream& operator<<(std::ostream& stream, const CtOp& op);

}  // namespace janncy

#endif  // JANNCY_CT_OP_H_
