#ifndef JANNCY_TENSOR_H_
#define JANNCY_TENSOR_H_

#include <functional>
#include <numeric>
#include <vector>

#include "include/panic.h"
#include "include/shape.h"

namespace janncy {

class Tensor {
  using Scalar = float;

 public:
  Tensor(std::vector<Scalar> values, Shape shape)
      : values_(values), shape_(shape) {
    PANIC_IF(shape_.ValueCnt() != values_.size());
  }

  Shape shape() const { return shape_; }

  Scalar at(const std::vector<int>& indices) const {
    PANIC_IF(indices.size() != shape_.dimension_count());
    int idx = 0;
    std::vector<int> multiplicands;
    std::partial_sum(shape_.begin() + 1, shape_.end(),
                     std::back_inserter(multiplicands), std::multiplies<int>());
    std::reverse(multiplicands.begin(), multiplicands.end());
    multiplicands.push_back(1);
    for (int dim_idx = 0; dim_idx < shape_.dimension_count(); dim_idx++) {
      PANIC_IF(indices[dim_idx] >= shape_[dim_idx]);
      idx += multiplicands[dim_idx] * indices[dim_idx];
    }
    return values_.at(idx);
  }

  int dimension_count() const { return shape_.dimension_count(); }

 private:
  std::vector<Scalar> values_;
  Shape shape_;
};

}  // namespace janncy

#endif  // JANNCY_TENSOR_H_
