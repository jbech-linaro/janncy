#include "include/MaxPool.hpp"

#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"
#include "include/Tensor.hpp"
#include "include/utils.hpp"

#include <iostream>

MaxPool::MaxPool(FlowNode* parent, Tensor pool, int stride, bool padding)
    : FlowNode({parent},
               Tensor({pool.shape()[0],
                       get_output_width(parent, pool, stride, padding),
                       get_output_height(parent, pool, stride, padding)})),
      pool_(pool),
      stride_(stride),
      padding_(padding) {}

int MaxPool::stride() const { return stride_; }
int MaxPool::padding() const { return padding_; }
Tensor MaxPool::pool() const { return pool_; }
void MaxPool::visit(FlowVisitor* visitor) { visitor->visit(this); }
