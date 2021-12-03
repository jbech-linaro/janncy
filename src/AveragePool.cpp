#include "include/AveragePool.hpp"

#include "include/Tensor.hpp"
#include "include/FlowNode.hpp"
#include "include/utils.hpp"

AveragePool::AveragePool(FlowNode* parent, Tensor pool, int stride, bool padded)
        : FlowNode({parent},
                Tensor({pool.shape()[0],
                get_output_width(parent, pool, stride, padded),
                get_output_height(parent, pool, stride, padded)})),
        stride_(stride),
        padded_(padded) {}

int AveragePool::stride() const {
    return stride_;
}

bool AveragePool::padded() const {
    return padded_;
}
