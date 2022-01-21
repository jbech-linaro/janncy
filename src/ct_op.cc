#include "include/ct_op.h"

#include <ostream>

namespace janncy {

std::ostream& operator<<(std::ostream& stream, const CtOp& op) {
  return stream << op.op_type() << "@" << &op << "";
}

}  // namespace janncy
