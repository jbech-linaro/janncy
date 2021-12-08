#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class Flow;

class Input : public FlowNode {
  public:
    static Input* create(Flow* flow, Tensor input_tensor) {
        return new Input(flow, input_tensor);
    }
    std::string type_str() const { return "Input"; }
    CtTensor cipherfy(std::vector<CtTensor> parents) const;

  private:
    Input(Flow* flow, Tensor input_tensor);
};

#endif  // INPUT_HPP_
