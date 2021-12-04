#ifndef BATCHNORMALIZATION_HPP_
#define BATCHNORMALIZATION_HPP_

#include "Tensor.hpp"
#include "FlowNode.hpp"

class BatchNormalization : public FlowNode {
public:
    BatchNormalization(FlowNode* parent);
    std::string type_str() const { return "BatchNormalization"; }
    CtTensor cipherfy(CtGraph& ct_graph, std::vector<CtTensor> parents) const;
};

#endif  // BATCHNORMALIZATION_HPP_
