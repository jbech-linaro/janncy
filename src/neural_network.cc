#include "include/neural_network.h"

#include "include/add_layer.h"
#include "include/average_pool_layer.h"
#include "include/batch_normalization_layer.h"
#include "include/conv_layer.h"
#include "include/flatten_layer.h"
#include "include/fully_connected_layer.h"
#include "include/input_layer.h"
#include "include/max_pool_layer.h"
#include "include/panic.h"
#include "include/relu_layer.h"
#include "include/shape.h"

namespace janncy {

namespace neural_network {

const Layer& CreateAdd(NeuralNetwork& nn, const Layer& parent0,
                       const Layer& parent1) {
  PANIC_IF(parent0.shape() != parent1.shape());
  Shape shape = parent0.shape();
  return nn.AddNode(std::make_unique<AddLayer>(shape), {&parent0, &parent1});
}

const Layer& CreateConvLayer(NeuralNetwork& nn, const Layer& parent,
                             KernelAttributes kernel, int output_channel_cnt) {
  return nn.AddNode(
      std::make_unique<ConvLayer>(parent.shape(), kernel, output_channel_cnt),
      {&parent});
}

const Layer& CreateAveragePool(NeuralNetwork& nn, const Layer& parent,
                               KernelAttributes kernel) {
  return nn.AddNode(std::make_unique<AveragePoolLayer>(parent.shape(), kernel),
                    {&parent});
}
const Layer& CreateMaxPool(NeuralNetwork& nn, const Layer& parent,
                           KernelAttributes kernel) {
  return nn.AddNode(std::make_unique<MaxPoolLayer>(parent.shape(), kernel),
                    {&parent});
}

const Layer& CreateBatchNormalization(NeuralNetwork& nn, const Layer& parent) {
  return nn.AddNode(std::make_unique<BatchNormalizationLayer>(parent.shape()),
                    {&parent});
}

const Layer& CreateGlobalAveragePool(NeuralNetwork& nn, const Layer& parent) {
  Shape kernel_shape = parent.shape().SpatialShape();
  std::vector<int> strides(kernel_shape.begin(), kernel_shape.end());
  KernelAttributes kernel(kernel_shape, strides, {});
  return CreateAveragePool(nn, parent, kernel);
}

const Layer& CreateInput(NeuralNetwork& nn, Shape shape) {
  return nn.AddNode(std::make_unique<InputLayer>(std::move(shape)), {});
}
const Layer& CreateRelu(NeuralNetwork& nn, const Layer& parent) {
  return nn.AddNode(std::make_unique<ReluLayer>(parent.shape()), {&parent});
}
const Layer& CreateFlatten(NeuralNetwork& nn, const Layer& parent) {
  return nn.AddNode(std::make_unique<FlattenLayer>(parent.shape()), {&parent});
}
const Layer& CreateFullyConnected(NeuralNetwork& nn, const Layer& parent,
                                  int output_dim) {
  Shape input_shape = parent.shape();
  PANIC_IF(input_shape.dimension_cnt() != 1,
           "Fully-connected layer expects 1D input", input_shape);
  int input_dim = input_shape[0];
  return nn.AddNode(
      std::make_unique<FullyConnectedLayer>(input_dim, output_dim), {&parent});
}

}  // namespace neural_network

}  // namespace janncy
