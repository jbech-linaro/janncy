#include "include/AveragePool.hpp"

#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"
#include "include/Tensor.hpp"
#include "include/utils.hpp"

#include <iostream>

AveragePool::AveragePool(FlowNode* parent, Tensor pool, int stride, bool padded)
    : FlowNode({parent},
               Tensor({pool.shape()[0],
                       get_output_width(parent, pool, stride, padded),
                       get_output_height(parent, pool, stride, padded)})),
      pool_(pool),
      stride_(stride),
      padded_(padded) {}

int AveragePool::stride() const { return stride_; }
bool AveragePool::padded() const { return padded_; }
Tensor AveragePool::pool() const { return pool_; }
void AveragePool::visit(FlowVisitor* visitor) { visitor->visit(this); }

int log2(int n) {
    if (n == 1) {
        return 0;
    }
    return 1 + log2(n >> 1);
}

