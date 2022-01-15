#include "include/Flow.hpp"

#include "include/Add.hpp"
#include "include/AveragePool.hpp"
#include "include/ConvLayer.hpp"
#include "include/Flatten.hpp"
#include "include/FullyConnected.hpp"
#include "include/Input.hpp"
#include "include/MaxPool.hpp"
#include "include/Panic.hpp"
#include "include/ReLU.hpp"

namespace janncy {

namespace flow {

FlowNode* create_add(Flow& flow, std::vector<const FlowNode*> parents) {
  if (parents.empty()) {
    PANIC("Empty add");
  }
  std::vector<int> shape = parents[0]->shape();
  for (const FlowNode* par : parents) {
    if (par->shape() != shape) {
      PANIC("All add inputs must have the same shape!", shape, par->shape());
    }
  }
  return flow.add_node(new Add(shape), parents);
}

FlowNode* create_conv_layer(Flow& flow, const FlowNode* parent,
                            KernelAttributes kernel, int output_channel_cnt) {
  return flow.add_node(
      new ConvLayer(parent->shape(), kernel, output_channel_cnt), {parent});
}
FlowNode* create_average_pool(Flow& flow, const FlowNode* parent,
                              KernelAttributes kernel) {
  return flow.add_node(new AveragePool(parent->shape(), kernel), {parent});
}
FlowNode* create_max_pool(Flow& flow, const FlowNode* parent,
                          KernelAttributes kernel) {
  return flow.add_node(new MaxPool(parent->shape(), kernel), {parent});
}
FlowNode* create_global_average_pool(Flow& flow, const FlowNode* parent) {
  auto input_shape = parent->shape();
  auto kernel_shape =
      std::vector<int>(input_shape.begin() + 1, input_shape.end());
  KernelAttributes kernel(kernel_shape, kernel_shape, {});
  return create_average_pool(flow, parent, kernel);
}

FlowNode* create_input(Flow& flow, std::vector<int> shape) {
  return flow.add_node(new Input(std::move(shape)), {});
}
FlowNode* create_relu(Flow& flow, const FlowNode* parent) {
  return flow.add_node(new ReLU(parent->shape()), {parent});
}
FlowNode* create_flatten(Flow& flow, const FlowNode* parent) {
  return flow.add_node(new Flatten(parent->shape()), {parent});
}
FlowNode* create_fully_connected(Flow& flow, const FlowNode* parent,
                                 int output_dim) {
  std::vector<int> input_shape = parent->shape();
  if (input_shape.size() != 1) {
    PANIC("Fully-connected layer expects 1D input", input_shape);
  }

  int input_dim = input_shape[0];
  return flow.add_node(new FullyConnected(input_dim, output_dim), {parent});
}

}  // namespace flow

}  // namespace janncy
