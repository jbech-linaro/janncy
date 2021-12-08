#include "include/BatchNormalization.hpp"

#include "include/CtPtAdd.hpp"
#include "include/CtPtMul.hpp"

#include <iostream>

BatchNormalization::BatchNormalization(FlowNode* parent)
    : FlowNode({parent}, parent->output_tensor()) {}

CtOp* batch_norm(CtOp* parent) {
    auto tmp = CtPtAdd::create(parent);
    return CtPtMul::create(tmp);
}

CtTensor BatchNormalization::cipherfy(std::vector<CtTensor> parents) const {
    auto parent = parents[0].get_ct_ops();
    std::vector<CtOp*> result;
    for (auto& ct_op : parent) {
        result.push_back(batch_norm(ct_op));
    }
    return CtTensor(result);
}
