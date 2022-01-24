#include "include/layer.h"

#include <ostream>

#include "include/utils.h"

namespace janncy {

std::ostream& operator<<(std::ostream& stream, const Layer& node) {
  return stream << node.op_type() << "@" << &node << " " << node.shape();
}

}  // namespace janncy
