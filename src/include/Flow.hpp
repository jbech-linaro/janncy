#ifndef FLOW_HPP_
#define FLOW_HPP_

#include "FlowNode.hpp"

#include <vector>

class Flow {
public:
    FlowNode* input(Tensor input_tensor);
    FlowNode* conv_layer(FlowNode* parent, Tensor filter, int stride);
    FlowNode* batch_normalization(FlowNode* parent);
    FlowNode* average_pool(FlowNode* parent, Tensor pool, int stride);
    FlowNode* fully_connected(FlowNode* parent, Tensor matrix);
    std::string str() const;
private:
    std::vector<FlowNode*> nodes;
};

#endif  // FLOWNODE_HPP_
