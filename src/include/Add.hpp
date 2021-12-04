#ifndef ADD_HPP_
#define ADD_HPP_

#include "FlowNode.hpp"

class Add : public FlowNode {
public:
    Add(FlowNode* parent0, FlowNode* parent1);
    std::string type_str() const { return "Add"; }
    CtTensor cipherfy(CtGraph& ct_graph, std::vector<CtTensor> parents) const;
};

#endif  // ADD_HPP_
