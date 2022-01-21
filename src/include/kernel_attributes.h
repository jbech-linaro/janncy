#ifndef JANNCY_KERNEL_ATTRIBUTES_H_
#define JANNCY_KERNEL_ATTRIBUTES_H_

#include <vector>

#include "shape.h"

namespace janncy {

class KernelAttributes {
 public:
  // `kernel_shape` includes only the spacial dimensions of the kernel,
  //                i.e, it must have the same number of dimensions as
  //                `stride` and `padding`.
  // `stride` defaults to `1` along all dimensions
  // `padding` defaults to `0` along all dimensions
  KernelAttributes(Shape kernel_shape, std::vector<int> strides = {},
                   std::vector<int> pads = {});

  int dim_cnt() const;
  const Shape& kernel_shape() const;
  const std::vector<int>& strides() const;
  const std::vector<int>& begin_pads() const;
  const std::vector<int>& end_pads() const;

  Shape output_shape(const Shape& input_shape, int output_channels) const;
  Shape output_shape(const Shape& Shape) const;

 private:
  Shape kernel_shape_;
  std::vector<int> strides_;
  std::vector<int> begin_pads_;
  std::vector<int> end_pads_;
};

}  // namespace janncy

#endif  // JANNCY_KERNEL_ATTRIBUTES_H_
