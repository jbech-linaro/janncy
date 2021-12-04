#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "Tensor.hpp"
#include "FlowNode.hpp"

class Input : public FlowNode {
public:
    Input(Tensor input_tensor);
    std::string type_str() const { return "Input"; }
    CtTensor cipherfy(CtGraph& ct_graph, std::vector<CtTensor> parents) const;
};

#endif  // INPUT_HPP_
