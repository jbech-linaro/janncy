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

namespace flow {

const FlowNode& CreateAdd(Flow& flow, const FlowNode& parent0,
                          const FlowNode& parent1) {
  PANIC_IF(parent0.shape() != parent1.shape());
  Shape shape = parent0.shape();
  return flow.AddNode(std::make_unique<Add>(shape), {&parent0, &parent1});
}

const FlowNode& CreateConvLayer(Flow& flow, const FlowNode& parent,
                                KernelAttributes kernel,
                                int output_channel_cnt) {
  return flow.AddNode(
      std::make_unique<ConvLayer>(parent.shape(), kernel, output_channel_cnt),
      {&parent});
}

const FlowNode& CreateAveragePool(Flow& flow, const FlowNode& parent,
                                  KernelAttributes kernel) {
  return flow.AddNode(std::make_unique<AveragePool>(parent.shape(), kernel),
                      {&parent});
}
const FlowNode& CreateMaxPool(Flow& flow, const FlowNode& parent,
                              KernelAttributes kernel) {
  return flow.AddNode(std::make_unique<MaxPool>(parent.shape(), kernel),
                      {&parent});
}

const FlowNode& CreateGlobalAveragePool(Flow& flow, const FlowNode& parent) {
  Shape kernel_shape = parent.shape().SpatialShape();
  std::vector<int> strides(kernel_shape.begin(), kernel_shape.end());
  KernelAttributes kernel(kernel_shape, strides, {});
  return CreateAveragePool(flow, parent, kernel);
}

const FlowNode& CreateInput(Flow& flow, Shape shape) {
  return flow.AddNode(std::make_unique<Input>(std::move(shape)), {});
}
const FlowNode& CreateRelu(Flow& flow, const FlowNode& parent) {
  return flow.AddNode(std::make_unique<ReLU>(parent.shape()), {&parent});
}
const FlowNode& CreateFlatten(Flow& flow, const FlowNode& parent) {
  return flow.AddNode(std::make_unique<Flatten>(parent.shape()), {&parent});
}
const FlowNode& CreateFullyConnected(Flow& flow, const FlowNode& parent,
                                     int output_dim) {
  Shape input_shape = parent.shape();
  PANIC_IF(input_shape.dimension_cnt() != 1,
           "Fully-connected layer expects 1D input", input_shape);
  int input_dim = input_shape[0];
  return flow.AddNode(std::make_unique<FullyConnected>(input_dim, output_dim),
                      {&parent});
}

}  // namespace flow

}  // namespace janncy
