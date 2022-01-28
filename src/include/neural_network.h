#ifndef JANNCY_NEURAL_NETWORK_H_
#define JANNCY_NEURAL_NETWORK_H_

#include <vector>

#include "include/dag.h"
#include "include/kernel_attributes.h"
#include "include/layer.h"

namespace janncy {

using NeuralNetwork = Dag<Layer>;

namespace neural_network {

const Layer& CreateAdd(NeuralNetwork& nn, const Layer& parent0,
                       const Layer& parent1);

const Layer& CreateConvLayer(NeuralNetwork& nn, const Layer& parent,
                             KernelAttributes kernel, int output_channel_cnt);
const Layer& CreateAveragePool(NeuralNetwork& nn, const Layer& parent,
                               KernelAttributes kernel);
const Layer& CreateMaxPool(NeuralNetwork& nn, const Layer& parent,
                           KernelAttributes kernel);
const Layer& CreateGlobalAveragePool(NeuralNetwork& nn, const Layer& parent);
const Layer& CreateBatchNormalization(NeuralNetwork& nn, const Layer& parent);

const Layer& CreateInput(NeuralNetwork& nn, Shape shape);
const Layer& CreateRelu(NeuralNetwork& nn, const Layer& parent);
const Layer& CreateFlatten(NeuralNetwork& nn, const Layer& parent);
const Layer& CreateFullyConnected(NeuralNetwork& nn, const Layer& parent,
                                  int output_dim);
}  // namespace neural_network

}  // namespace janncy

#endif  // JANNCY_NEURAL_NETWORK_H_
