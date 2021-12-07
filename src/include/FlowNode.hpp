#ifndef FLOWNODE_HPP_
#define FLOWNODE_HPP_

#include "CtTensor.hpp"
#include "Node.hpp"
#include "Tensor.hpp"

#include <string>
#include <vector>

class CtGraph;

class FlowNode : public Node<FlowNode> {
  public:
    FlowNode(std::vector<FlowNode*> parents, Tensor output_tensor);
    Tensor output_tensor() const;
    Tensor input_tensor() const;

    virtual CtTensor cipherfy(CtGraph& ct_graph,
                              std::vector<CtTensor> parents) const = 0;

    void set_name(std::string name);

    std::string str() const;
    virtual std::string type_str() const = 0;

    Tensor output_tensor_;
    std::string name_;
};

#endif  // FLOWNODE_HPP_
