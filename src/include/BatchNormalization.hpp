#ifndef BATCHNORMALIZATION_HPP_
#define BATCHNORMALIZATION_HPP_

#include "Tensor.hpp"
#include "FlowNode.hpp"

class BatchNormalization : public FlowNode {
public:
    BatchNormalization(FlowNode* parent);
    std::string type_str() const { return "BatchNormalization"; }
};

#endif  // BATCHNORMALIZATION_HPP_
