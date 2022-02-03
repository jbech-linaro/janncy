#ifndef JANNCY_LAYER_H_
#define JANNCY_LAYER_H_

#include <string>
#include <vector>

#include "include/shape.h"

namespace janncy {

class LayerVisitor;

class Layer {
 public:
  Layer() = default;
  Layer(Layer&&) = default;
  virtual ~Layer() {}
  Layer(const Layer&) = delete;
  Layer& operator=(const Layer&) = delete;
  Layer& operator=(const Layer&&) = default;

  virtual void Accept(LayerVisitor& visitor) const = 0;
  virtual std::string op_type() const = 0;
  virtual Shape shape() const = 0;
};

std::ostream& operator<<(std::ostream& stream, const Layer& node);

}  // namespace janncy

#endif  // JANNCY_LAYER_H_
