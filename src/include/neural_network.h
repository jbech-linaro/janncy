#ifndef JANNCY_NEURAL_NETWORK_H_
#define JANNCY_NEURAL_NETWORK_H_

#include <vector>

#include "include/dag.h"
#include "include/kernel_attributes.h"
#include "include/layer.h"

namespace janncy {

using Flow = Graph<FlowNode>;

namespace flow {

const FlowNode& CreateAdd(Flow& flow, const FlowNode& parent0,
                          const FlowNode& parent1);

const FlowNode& CreateConvLayer(Flow& flow, const FlowNode& parent,
                                KernelAttributes kernel,
                                int output_channel_cnt);
const FlowNode& CreateAveragePool(Flow& Flow, const FlowNode& parent,
                                  KernelAttributes kernel);
const FlowNode& CreateMaxPool(Flow& flow, const FlowNode& parent,
                              KernelAttributes kernel);
const FlowNode& CreateGlobalAveragePool(Flow& flow, const FlowNode& parent);

const FlowNode& CreateInput(Flow& flow, Shape shape);
const FlowNode& CreateRelu(Flow& flow, const FlowNode& parent);
const FlowNode& CreateFlatten(Flow& flow, const FlowNode& parent);
const FlowNode& CreateFullyConnected(Flow& flow, const FlowNode& parent,
                                     int output_dim);
}  // namespace flow

}  // namespace janncy

#endif  // JANNCY_NEURAL_NETWORK_H_
