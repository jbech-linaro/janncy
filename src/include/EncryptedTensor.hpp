#ifndef ENCRYPTED_TENSOR_HPP_
#define ENCRYPTED_TENSOR_HPP_

#include "Tensor.hpp"

#include <vector>

class EncryptedTensor {
public:
    EncryptedTensor(Tensor tensor);
    std::vector<int> shape() const;
private:
    Tensor tensor_;
};

#endif  // ENCRYPTED_TENSOR_HPP_
