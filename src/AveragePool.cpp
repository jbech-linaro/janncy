#include "include/AveragePool.hpp"

#include "include/Tensor.hpp"
#include "include/FlowNode.hpp"

AveragePool::AveragePool(FlowNode* parent, Tensor pool, int stride)
        : FlowNode(parent,
                Tensor({pool.shape()[0],
                    (parent->output_tensor().shape()[1] - 2*(pool.shape()[2]/2)) / stride,
                    (parent->output_tensor().shape()[1] - 2*(pool.shape()[3]/2)) / stride})),
        stride_(stride) {}

int AveragePool::stride() const {
    return stride_;
}
