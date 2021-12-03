#ifndef ADD_HPP_
#define ADD_HPP_

#include "FlowNode.hpp"

class Add : public FlowNode {
public:
    Add(FlowNode* parent0, FlowNode* parent1);
    std::string type_str() const { return "Add"; }
};

#endif  // ADD_HPP_
