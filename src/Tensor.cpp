#include "include/Tensor.hpp"

#include <vector>

Tensor::Tensor(std::vector<int> shape) : shape_(shape) {}

std::vector<int> Tensor::shape() const {
    return shape_;
}
