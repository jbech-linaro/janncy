#include "include/AveragePool.hpp"

#include "include/Tensor.hpp"
#include "include/FlowNode.hpp"
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

int AveragePool::stride() const {
    return stride_;
}

bool AveragePool::padded() const {
    return padded_;
}

int log2(int n) {
    if (n == 1) {
        return 0;
    }
    return 1 + log2(n>>1);
}

CtTensor AveragePool::cipherfy(CtGraph& ct_graph, std::vector<CtTensor> parents) const {
    auto parent = parents[0].get_ct_ops();
    auto result = parent;
    for (auto channel_idx = 0ul; channel_idx < parent.size(); ++channel_idx) {
        for (auto idx = 0; idx < log2(pool_.shape()[1]); ++idx) {
           auto rot = ct_graph.rotate(result[channel_idx]);
           result[channel_idx] = ct_graph.add(result[channel_idx], rot);
        }
        for (auto idx = 0; idx < log2(pool_.shape()[1]); ++idx) {
           auto rot = ct_graph.rotate(result[channel_idx]);
           result[channel_idx] = ct_graph.add(result[channel_idx], rot);
        }
    }
    return CtTensor(result);
}
