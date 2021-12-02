#ifndef FLOWNODE_HPP_
#define FLOWNODE_HPP_

#include "Tensor.hpp"

class FlowNode {
public:
    FlowNode(Tensor input_tensor, Tensor output_tensor);
    Tensor output_tensor() const;
    Tensor input_tensor() const;
protected:
    Tensor input_tensor_;
    Tensor output_tensor_;
};

#endif  // FLOWNODE_HPP_
