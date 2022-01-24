#include "include/neural_network.h"

#include "include/add.h"
#include "include/average_pool.h"
#include "include/conv_layer.h"
#include "include/flatten.h"
#include "include/fully_connected.h"
#include "include/input.h"
#include "include/max_pool.h"
#include "include/panic.h"
#include "include/relu.h"
#include "include/shape.h"

namespace janncy {

namespace neural_network {

const FlowNode& CreateAdd(NeuralNetwork& nn, const FlowNode& parent0,
                          const FlowNode& parent1) {
  PANIC_IF(parent0.shape() != parent1.shape());
  Shape shape = parent0.shape();
  return nn.AddNode(std::make_unique<Add>(shape), {&parent0, &parent1});
}

const FlowNode& CreateConvLayer(NeuralNetwork& nn, const FlowNode& parent,
                                KernelAttributes kernel,
                                int output_channel_cnt) {
  return nn.AddNode(
      std::make_unique<ConvLayer>(parent.shape(), kernel, output_channel_cnt),
      {&parent});
}

const FlowNode& CreateAveragePool(NeuralNetwork& nn, const FlowNode& parent,
                                  KernelAttributes kernel) {
  return nn.AddNode(std::make_unique<AveragePool>(parent.shape(), kernel),
                    {&parent});
}
const FlowNode& CreateMaxPool(NeuralNetwork& nn, const FlowNode& parent,
                              KernelAttributes kernel) {
  return nn.AddNode(std::make_unique<MaxPool>(parent.shape(), kernel),
                    {&parent});
}

const FlowNode& CreateGlobalAveragePool(NeuralNetwork& nn,
                                        const FlowNode& parent) {
  Shape kernel_shape = parent.shape().SpatialShape();
  std::vector<int> strides(kernel_shape.begin(), kernel_shape.end());
  KernelAttributes kernel(kernel_shape, strides, {});
  return CreateAveragePool(nn, parent, kernel);
}

const FlowNode& CreateInput(NeuralNetwork& nn, Shape shape) {
  return nn.AddNode(std::make_unique<Input>(std::move(shape)), {});
}
const FlowNode& CreateRelu(NeuralNetwork& nn, const FlowNode& parent) {
  return nn.AddNode(std::make_unique<ReLU>(parent.shape()), {&parent});
}
const FlowNode& CreateFlatten(NeuralNetwork& nn, const FlowNode& parent) {
  return nn.AddNode(std::make_unique<Flatten>(parent.shape()), {&parent});
}
const FlowNode& CreateFullyConnected(NeuralNetwork& nn, const FlowNode& parent,
                                     int output_dim) {
  Shape input_shape = parent.shape();
  PANIC_IF(input_shape.dimension_cnt() != 1,
           "Fully-connected layer expects 1D input", input_shape);
  int input_dim = input_shape[0];
  return nn.AddNode(std::make_unique<FullyConnected>(input_dim, output_dim),
                    {&parent});
}

}  // namespace neural_network

}  // namespace janncy
