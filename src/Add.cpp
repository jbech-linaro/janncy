#include "include/Add.hpp"

#include "include/CtAdd.hpp"
#include "include/CtTensor.hpp"

#include <vector>

Add::Add(FlowNode* parent0, FlowNode* parent1)
    : FlowNode({parent0, parent1}, parent0->output_tensor(), parent0->flow()) {}

CtTensor Add::cipherfy(std::vector<CtTensor> parents) const {
    auto parent0 = parents[0].get_ct_ops();
    auto parent1 = parents[1].get_ct_ops();
    std::vector<CtOp*> result;
    for (auto idx = 0ul; idx < parent0.size(); ++idx) {
        result.push_back(CtAdd::create(parent0[idx], parent1[idx]));
    }
    return CtTensor(result);
}
