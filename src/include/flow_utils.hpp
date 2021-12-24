#ifndef FLOW_UTILS_HPP_
#define FLOW_UTILS_HPP_

#include <vector>

class Flow;
class FlowNode;

class Add;
class AveragePool;
class BatchNormalization;
class ConvLayer;
class Flatten;
class FullyConnected;
class MaxPool;
class Input;
class ReLU;

Add* add(Flow* flow, std::vector<FlowNode*> parents);

AveragePool* average_pool(Flow* flow, FlowNode* parent,
                          const std::vector<int>& kernel_shape,
                          const std::vector<int>& stride,
                          const std::vector<int>& padding);

BatchNormalization* batch_normalization(Flow* flow, FlowNode* parent);

ConvLayer* conv_layer(Flow* flow, FlowNode* parent,
                      const std::vector<int>& kernel_shape,
                      const std::vector<int>& stride,
                      const std::vector<int>& padding);

Flatten* flatten(Flow* flow, FlowNode* parent, int axis);

FullyConnected* fully_connected(Flow* flow, FlowNode* parent,
                                const std::vector<int>& kernel_shape);

Input* input(Flow* flow, const std::vector<int>& input_shape);

MaxPool* max_pool(Flow* flow, FlowNode* parent,
                  const std::vector<int>& kernel_shape,
                  const std::vector<int>& stride,
                  const std::vector<int>& padding);

ReLU* relu(Flow* flow, FlowNode* parent);

std::vector<int> get_shape_average_pool(const std::vector<int>& input_shape,
                                        const std::vector<int>& kernel_shape,
                                        const std::vector<int>& stride,
                                        const std::vector<int>& padding);

std::vector<int> get_shape_conv_layer(const std::vector<int>& input_shape,
                                      const std::vector<int>& kernel_shape,
                                      const std::vector<int>& stride,
                                      const std::vector<int>& padding);

std::vector<int> get_shape_max_pool(const std::vector<int>& input_shape,
                                    const std::vector<int>& kernel_shape,
                                    const std::vector<int>& stride,
                                    const std::vector<int>& padding);

std::vector<int> get_shape_fully_connected(
    const std::vector<int>& input_shape, const std::vector<int>& kernel_shape);

std::vector<int> get_shape_flatten(const std::vector<int>& input_shape,
                                   int axis);

#endif  // FLOW_UTILS_HPP_
