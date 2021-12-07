#include "include/BatchNormalization.hpp"
#include "include/CtGraph.hpp"

#include <iostream>

BatchNormalization::BatchNormalization(FlowNode* parent)
    : FlowNode({parent}, parent->output_tensor()) {}

CtOp* batch_norm(CtGraph& ct_graph, CtOp* parent) {
    auto tmp = ct_graph.add_pt(parent);
    return ct_graph.mul_pt(tmp);
}

CtTensor BatchNormalization::cipherfy(CtGraph& ct_graph,
                                      std::vector<CtTensor> parents) const {
    auto parent = parents[0].get_ct_ops();
    std::vector<CtOp*> result;
    for (auto& ct_op : parent) {
        result.push_back(batch_norm(ct_graph, ct_op));
    }
    return CtTensor(result);
}
