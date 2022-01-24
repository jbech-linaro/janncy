#ifndef JANNCY_NEURAL_NETWORK_H_
#define JANNCY_NEURAL_NETWORK_H_

#include <vector>

#include "include/dag.h"
#include "include/kernel_attributes.h"
#include "include/layer.h"

namespace janncy {

using NeuralNetwork = Dag<FlowNode>;

namespace neural_network {

const FlowNode& CreateAdd(NeuralNetwork& nn, const FlowNode& parent0,
                          const FlowNode& parent1);

const FlowNode& CreateConvLayer(NeuralNetwork& nn, const FlowNode& parent,
                                KernelAttributes kernel,
                                int output_channel_cnt);
const FlowNode& CreateAveragePool(NeuralNetwork& nn, const FlowNode& parent,
                                  KernelAttributes kernel);
const FlowNode& CreateMaxPool(NeuralNetwork& nn, const FlowNode& parent,
                              KernelAttributes kernel);
const FlowNode& CreateGlobalAveragePool(NeuralNetwork& nn,
                                        const FlowNode& parent);

const FlowNode& CreateInput(NeuralNetwork& nn, Shape shape);
const FlowNode& CreateRelu(NeuralNetwork& nn, const FlowNode& parent);
const FlowNode& CreateFlatten(NeuralNetwork& nn, const FlowNode& parent);
const FlowNode& CreateFullyConnected(NeuralNetwork& nn, const FlowNode& parent,
                                     int output_dim);
}  // namespace neural_network

}  // namespace janncy

#endif  // JANNCY_NEURAL_NETWORK_H_
