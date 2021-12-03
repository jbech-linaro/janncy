#ifndef FLOWNODE_HPP_
#define FLOWNODE_HPP_

#include "Tensor.hpp"
#include "Node.hpp"

#include <string>
#include <vector>

class FlowNode : public Node {
public:
    FlowNode(std::vector<FlowNode*> parents, Tensor output_tensor);
    Tensor output_tensor() const;
    Tensor input_tensor() const;

    void set_name(std::string name);

    std::string str() const;
    virtual std::string type_str() const = 0;

protected:
    std::vector<FlowNode*> parents_;
    Tensor output_tensor_;
    std::string name_;
};

#endif  // FLOWNODE_HPP_
