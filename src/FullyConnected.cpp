#include "include/FullyConnected.hpp"
#include "include/CtAdd.hpp"
#include "include/CtPtMul.hpp"

#include <iostream>

FullyConnected::FullyConnected(FlowNode* parent, Tensor matrix)
    : FlowNode({parent}, Tensor({matrix.shape()[1]})) {}

CtTensor FullyConnected::cipherfy(std::vector<CtTensor> parents) const {
    auto parent = parents[0].get_ct_ops();
    auto result = std::vector<CtOp*>(output_tensor().shape()[0], nullptr);
    for (auto idx = 0ul; idx < result.size(); ++idx) {
        for (auto& ct : parent) {
            auto tmp = CtPtMul::create(ct);
            if (result[idx]) {
                result[idx] = CtAdd::create(result[idx], tmp);
            } else {
                result[idx] = tmp;
            }
        }
    }

    return CtTensor(result);
}
