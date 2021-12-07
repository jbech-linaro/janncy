#include "include/FullyConnected.hpp"
#include "include/CtGraph.hpp"

#include <iostream>

FullyConnected::FullyConnected(FlowNode* parent, Tensor matrix)
    : FlowNode({parent}, Tensor({matrix.shape()[1]})) {}

CtTensor FullyConnected::cipherfy(CtGraph& ct_graph,
                                  std::vector<CtTensor> parents) const {
    auto parent = parents[0].get_ct_ops();
    auto result = std::vector<CtOp*>(output_tensor().shape()[0], nullptr);
    for (auto idx = 0ul; idx < result.size(); ++idx) {
        for (auto& ct : parent) {
            auto tmp = ct_graph.mul_pt(ct);
            if (result[idx]) {
                result[idx] = ct_graph.add(result[idx], tmp);
            } else {
                result[idx] = tmp;
            }
        }
    }

    return CtTensor(result);
}
