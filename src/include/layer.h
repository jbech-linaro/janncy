#ifndef JANNCY_LAYER_H_
#define JANNCY_LAYER_H_

#include <string>
#include <vector>

#include "include/shape.h"

namespace janncy {

class LayerVisitor;

class Layer {
 public:
  virtual void Accept(LayerVisitor& visitor) const = 0;
  virtual std::string op_type() const = 0;
  virtual Shape shape() const = 0;

  virtual ~Layer() {}
};

std::ostream& operator<<(std::ostream& stream, const Layer& node);

}  // namespace janncy

#endif  // JANNCY_LAYER_H_
