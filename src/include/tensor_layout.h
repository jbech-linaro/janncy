#ifndef JANNCY_TENSOR_LAYOUT_H_
#define JANNCY_TENSOR_LAYOUT_H_

#include "include/chunk_layout.h"
#include "include/shape.h"

namespace janncy {

class TensorLayout {
 public:
  TensorLayout(ChunkLayout chunk_layout, Shape shape)
      : chunk_layout_(chunk_layout), shape_(shape) {}

  const ChunkLayout& chunk_layout() const { return chunk_layout_; }
  const Shape& shape() const { return shape_; }

 private:
  ChunkLayout chunk_layout_;
  Shape shape_;
};

}  // namespace janncy

#endif  // JANNCY_TENSOR_LAYOUT_H_
