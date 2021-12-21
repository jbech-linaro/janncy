#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "Tensor.hpp"

class FlowNode;

int get_output_width(const FlowNode* parent, const Tensor& filter, int stride,
                     bool padded);
int get_output_height(const FlowNode* parent, const Tensor& filter, int stride,
                      bool padded);
double get_uniform_random();

#endif  // UTILS_HPP_
