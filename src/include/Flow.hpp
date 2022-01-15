#ifndef FLOW_HPP_
#define FLOW_HPP_

#include <vector>

#include "FlowNode.hpp"
#include "Graph.hpp"
#include "KernelAttributes.hpp"

namespace janncy {

typedef Graph<FlowNode> Flow;

namespace flow {
FlowNode* create_add(Flow& flow, std::vector<const FlowNode*> parents);

FlowNode* create_conv_layer(Flow& flow, const FlowNode* parent,
                            KernelAttributes kernel,
                            int output_channel_cnt);
FlowNode* create_average_pool(Flow& Flow, const FlowNode* parent,
                              KernelAttributes kernel);
FlowNode* create_max_pool(Flow& flow, const FlowNode* parent,
                          KernelAttributes kernel);
FlowNode* create_global_average_pool(Flow& flow, const FlowNode* parent);

FlowNode* create_input(Flow& flow, std::vector<int> shape);
FlowNode* create_relu(Flow& flow, const FlowNode *parent);
FlowNode* create_flatten(Flow& flow, const FlowNode *parent);
FlowNode* create_fully_connected(Flow& flow, const FlowNode *parent,
                                 int output_dim);

}  // namespace flow

}  // namespace janncy

#endif  // FLOWNODE_HPP_
