#include "include/AveragePool.hpp"

#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"
#include "include/Tensor.hpp"
#include "include/utils.hpp"

#include <iostream>

AveragePool::AveragePool(FlowNode* parent, Tensor pool, int stride, int padding)
    : FlowNode({parent},
               Tensor({pool.shape()[0],
                       get_output_width(parent, pool, stride, padding),
                       get_output_height(parent, pool, stride, padding)})),
      pool_(pool),
      stride_(stride),
      padding_(padding) {}

int AveragePool::stride() const { return stride_; }
int AveragePool::padding() const { return padding_; }
Tensor AveragePool::pool() const { return pool_; }
void AveragePool::visit(FlowVisitor* visitor) { visitor->visit(this); }
