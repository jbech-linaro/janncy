#ifndef JANNCY_FLOW_H_
#define JANNCY_FLOW_H_

#include <vector>

#include "include/flow_node.h"
#include "include/graph.h"
#include "include/kernel_attributes.h"

namespace janncy {

typedef Graph<FlowNode> Flow;

namespace flow {
FlowNode* create_add(Flow& flow, std::vector<const FlowNode*> parents);

FlowNode* create_conv_layer(Flow& flow, const FlowNode* parent,
                            KernelAttributes kernel, int output_channel_cnt);
FlowNode* create_average_pool(Flow& Flow, const FlowNode* parent,
                              KernelAttributes kernel);
FlowNode* create_max_pool(Flow& flow, const FlowNode* parent,
                          KernelAttributes kernel);
FlowNode* create_global_average_pool(Flow& flow, const FlowNode* parent);

FlowNode* create_input(Flow& flow, std::vector<int> shape);
FlowNode* create_relu(Flow& flow, const FlowNode* parent);
FlowNode* create_flatten(Flow& flow, const FlowNode* parent);
FlowNode* create_fully_connected(Flow& flow, const FlowNode* parent,
                                 int output_dim);

}  // namespace flow

}  // namespace janncy

#endif  // JANNCY_FLOW_H_
