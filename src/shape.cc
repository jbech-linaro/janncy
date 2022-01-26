#include "include/shape.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <ostream>
#include <vector>

#include "include/ostream_utils.h"

namespace janncy {

int Shape::ValueCnt() const {
  return std::accumulate(begin(), end(), 1, std::multiplies<int>());
}

Shape Shape::SubShape(int start_i, int end_i) const {
  Shape result(end_i - start_i);
  std::copy(begin() + start_i, begin() + end_i, result.begin());
  return result;
}

Shape ShapeWithChannels(int channel_cnt, const Shape& spatial_shape) {
  Shape result(spatial_shape.dimension_cnt() + 1);
  result[0] = channel_cnt;
  std::copy(spatial_shape.begin(), spatial_shape.end(), result.begin() + 1);
  return result;
}

std::ostream& operator<<(std::ostream& stream, const Shape& shape) {
  return stream << "Shape" << std::vector<int>(shape.begin(), shape.end());
}

}  // namespace janncy
