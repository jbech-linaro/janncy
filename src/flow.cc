#include "include/flow.h"

#include "include/add.h"
#include "include/average_pool.h"
#include "include/conv_layer.h"
#include "include/flatten.h"
#include "include/fully_connected.h"
#include "include/input.h"
#include "include/max_pool.h"
#include "include/panic.h"
#include "include/relu.h"

namespace janncy {

namespace flow {

const FlowNode* CreateAdd(Flow& flow, std::vector<const FlowNode*> parents) {
  if (parents.empty()) {
    PANIC("Empty add");
  }
  std::vector<int> shape = parents[0]->shape();
  for (const FlowNode* par : parents) {
    if (par->shape() != shape) {
      PANIC("All add inputs must have the same shape!", shape, par->shape());
    }
  }
  return flow.AddNode(std::make_unique<Add>(shape), parents);
}

const FlowNode* CreateConvLayer(Flow& flow, const FlowNode* parent,
                                KernelAttributes kernel,
                                int output_channel_cnt) {
  return flow.AddNode(
      std::make_unique<ConvLayer>(parent->shape(), kernel, output_channel_cnt),
      {parent});
}

const FlowNode* CreateAveragePool(Flow& flow, const FlowNode* parent,
                                  KernelAttributes kernel) {
  return flow.AddNode(std::make_unique<AveragePool>(parent->shape(), kernel),
                      {parent});
}
const FlowNode* CreateMaxPool(Flow& flow, const FlowNode* parent,
                              KernelAttributes kernel) {
  return flow.AddNode(std::make_unique<MaxPool>(parent->shape(), kernel),
                      {parent});
}
const FlowNode* CreateGlobalAveragePool(Flow& flow, const FlowNode* parent) {
  const auto& input_shape = parent->shape();
  std::vector<int> kernel_shape(input_shape.begin() + 1, input_shape.end());
  KernelAttributes kernel(kernel_shape, kernel_shape, {});
  return CreateAveragePool(flow, parent, kernel);
}

const FlowNode* CreateInput(Flow& flow, std::vector<int> shape) {
  return flow.AddNode(std::make_unique<Input>(std::move(shape)), {});
}
const FlowNode* CreateRelu(Flow& flow, const FlowNode* parent) {
  return flow.AddNode(std::make_unique<ReLU>(parent->shape()), {parent});
}
const FlowNode* CreateFlatten(Flow& flow, const FlowNode* parent) {
  return flow.AddNode(std::make_unique<Flatten>(parent->shape()), {parent});
}
const FlowNode* CreateFullyConnected(Flow& flow, const FlowNode* parent,
                                     int output_dim) {
  std::vector<int> input_shape = parent->shape();
  if (input_shape.size() != 1) {
    PANIC("Fully-connected layer expects 1D input", input_shape);
  }

  int input_dim = input_shape[0];
  return flow.AddNode(std::make_unique<FullyConnected>(input_dim, output_dim),
                      {parent});
}

}  // namespace flow

}  // namespace janncy
