#ifndef JANNCY_FLOW_H_
#define JANNCY_FLOW_H_

#include <vector>

#include "include/flow_node.h"
#include "include/graph.h"
#include "include/kernel_attributes.h"

namespace janncy {

using Flow = Graph<FlowNode>;

namespace flow {
FlowNode* CreateAdd(Flow& flow, std::vector<const FlowNode*> parents);

FlowNode* CreateConvLayer(Flow& flow, const FlowNode* parent,
                          KernelAttributes kernel, int output_channel_cnt);
FlowNode* CreateAveragePool(Flow& Flow, const FlowNode* parent,
                            KernelAttributes kernel);
FlowNode* CreateMaxPool(Flow& flow, const FlowNode* parent,
                        KernelAttributes kernel);
FlowNode* CreateGlobalAveragePool(Flow& flow, const FlowNode* parent);

FlowNode* CreateInput(Flow& flow, std::vector<int> shape);
FlowNode* CreateRelu(Flow& flow, const FlowNode* parent);
FlowNode* CreateFlatten(Flow& flow, const FlowNode* parent);
FlowNode* CreateFullyConnected(Flow& flow, const FlowNode* parent,
                               int output_dim);

}  // namespace flow

}  // namespace janncy

#endif  // JANNCY_FLOW_H_
