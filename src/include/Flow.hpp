#ifndef FLOW_HPP_
#define FLOW_HPP_

#include <vector>

#include "FlowNode.hpp"
#include "Graph.hpp"
#include "KernelAttributes.hpp"

namespace janncy {

class Flow : public Graph<FlowNode> {
  public:
    FlowNode* create_add(std::vector<const FlowNode*> parents);

    FlowNode* create_conv_layer(const FlowNode* parent, KernelAttributes kernel,
                                int output_channel_cnt);
    FlowNode* create_average_pool(const FlowNode* parent,
                                  KernelAttributes kernel);
    FlowNode* create_max_pool(const FlowNode* parent, KernelAttributes kernel);
    FlowNode* create_global_average_pool(const FlowNode* parent);

    FlowNode* create_input(std::vector<int> shape);
    FlowNode* create_relu(const FlowNode *parent);
    FlowNode* create_flatten(const FlowNode *parent);
    FlowNode* create_fully_connected(const FlowNode *parent, int output_dim);

};

}  // namespace janncy

#endif  // FLOWNODE_HPP_
