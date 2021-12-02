#ifndef RELU_HPP_
#define RELU_HPP_

#include "Tensor.hpp"
#include "FlowNode.hpp"

class ReLU : public FlowNode {
public:
    ReLU(Tensor input_tensor);
private:
};

#endif  // RELU_HPP_
