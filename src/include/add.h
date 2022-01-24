#ifndef JANNCY_ADD_H_
#define JANNCY_ADD_H_

#include <string>
#include <vector>

#include "include/layer.h"
#include "include/shape.h"

namespace janncy {

class LayerVisitor;

class Add : public Layer {
 public:
  Add(Shape shape);

  void Accept(LayerVisitor& visitor) const override;
  std::string op_type() const override;
  Shape shape() const override;

 private:
  Shape shape_;
};

}  // namespace janncy

#endif  // JANNCY_ADD_H_
