#ifndef FLOWNODE_HPP_
#define FLOWNODE_HPP_

#include "Tensor.hpp"

#include <string>
#include <vector>

class FlowNode {
public:
    FlowNode(FlowNode* parent, Tensor output_tensor);
    Tensor output_tensor() const;
    Tensor input_tensor() const;

    void add_child(FlowNode* child);

    std::vector<FlowNode*> get_children() const { return children; }

    void set_name(std::string name);

    std::string str() const;

    virtual std::string type_str() const = 0;

protected:
    FlowNode* parent_;
    Tensor output_tensor_;
    std::vector<FlowNode*> children;
    std::string name_;
};

#endif  // FLOWNODE_HPP_
