#include "include/ConvLayer.hpp"

#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"
#include "include/Tensor.hpp"
#include "include/utils.hpp"

ConvLayer::ConvLayer(FlowNode* parent, Tensor filter, int stride, int padding)
    : FlowNode({parent},
               Tensor({filter.shape()[0],
                       get_output_width(parent, filter, stride, padding),
                       get_output_height(parent, filter, stride, padding)})),
      stride_(stride),
      filter_(filter),
      padding_(padding) {}

int ConvLayer::stride() const { return stride_; }
Tensor ConvLayer::filter() const { return filter_; }

int ConvLayer::padding() const { return padding_; }

void ConvLayer::visit(FlowVisitor* visitor) { visitor->visit(this); }
