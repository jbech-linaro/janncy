#ifndef FULLYCONNECTED_HPP_
#define FULLYCONNECTED_HPP_

#include "Tensor.hpp"
#include "FlowNode.hpp"

class FullyConnected : public FlowNode {
public:
    FullyConnected(FlowNode* parent, Tensor matrix);
    std::string type_str() const { return "FullyConnected"; }
    CtTensor cipherfy(CtGraph& ct_graph, std::vector<CtTensor> parents) const;
};

#endif  // FULLYCONNECTRED_HPP_
