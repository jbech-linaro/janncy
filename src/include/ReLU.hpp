#ifndef RELU_HPP_
#define RELU_HPP_

#include "Tensor.hpp"
#include "FlowNode.hpp"

class ReLU : public FlowNode {
public:
    ReLU(FlowNode* parent);
    std::string type_str() const { return "ReLU"; }
private:
};

#endif  // RELU_HPP_
