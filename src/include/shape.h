#ifndef JANNCY_SHAPE_H_
#define JANNCY_SHAPE_H_

#include <initializer_list>
#include <ostream>
#include <vector>

namespace janncy {

class Shape {
 public:
  using Iterator = std::vector<int>::iterator;
  using ConstIterator = std::vector<int>::const_iterator;

  Shape() {}
  Shape(int dimension_cnt) : dimensions_(dimension_cnt) {}
  Shape(std::initializer_list<int> l) : dimensions_(l) {}
  Shape(std::vector<int> v) : dimensions_(std::move(v)) {}
  template <typename InputIt>
  Shape(InputIt begin, InputIt end) : dimensions_(begin, end) {}

  friend bool operator==(const Shape& s1, const Shape& s2) {
    return s1.dimensions_ == s2.dimensions_;
  }
  friend bool operator!=(const Shape& s1, const Shape& s2) {
    return !(s1 == s2);
  }

  Iterator begin() { return dimensions_.begin(); }
  Iterator end() { return dimensions_.end(); }
  ConstIterator begin() const { return dimensions_.begin(); }
  ConstIterator end() const { return dimensions_.end(); }

  int operator[](int i) const { return dimensions_[i]; }
  int& operator[](int i) { return dimensions_[i]; }

  int dimension_cnt() const { return dimensions_.size(); }
  int channels() const { return dimensions_[0]; }
  int ValueCnt() const;

  Shape SubShape(int start_i, int end_i) const;
  Shape SubShape(int start_i) const {
    return SubShape(start_i, dimension_cnt());
  }
  Shape SpatialShape() const { return SubShape(1); }

 private:
  std::vector<int> dimensions_;
};

Shape ShapeWithChannels(int channel_cnt, const Shape& spatial_shape);

std::ostream& operator<<(std::ostream& stream, const Shape& shape);

}  // namespace janncy

#endif  // JANNCY_SHAPE_H_
