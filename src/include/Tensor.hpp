#ifndef TENSOR_HPP_
#define TENSOR_HPP_

#include <vector>

class Tensor {
  public:
    Tensor(std::vector<int> shape);
    std::vector<int> shape() const;

  private:
    std::vector<int> shape_;
};
#endif  // TENSOR_HPP_
