#include "include/ConvLayer.hpp"

#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"
#include "include/Tensor.hpp"
#include "include/utils.hpp"

#include <iostream>

ConvLayer::ConvLayer(FlowNode* parent, Tensor filter, int stride, bool padded)
    : FlowNode({parent},
               Tensor({filter.shape()[0],
                       get_output_width(parent, filter, stride, padded),
                       get_output_height(parent, filter, stride, padded)})),
      stride_(stride),
      filter_(filter),
      padded_(padded) {}

int ConvLayer::stride() const { return stride_; }
Tensor ConvLayer::filter() const { return filter_; }

bool ConvLayer::padded() const { return padded_; }

Tensor ConvLayer::output_tensor() const { return output_tensor_; }

void ConvLayer::visit(FlowVisitor* visitor) { visitor->visit(this); }
