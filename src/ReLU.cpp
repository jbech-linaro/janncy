#include "include/ReLU.hpp"

#include "include/CtGraph.hpp"
#include "include/FlowNode.hpp"

#include <iostream>

ReLU::ReLU(FlowNode* parent) : FlowNode({parent}, parent->output_tensor()) {}

int get_nearest_pow2(int n) {
    if (n == 1) {
        return 1;
    }
    return 2 * get_nearest_pow2(n >> 1);
}

CtOp* poly_eval(CtGraph& ct_graph, CtOp* parent, int degree) {
    (void)ct_graph;
    (void)degree;
    auto result = parent;
    std::vector<CtOp*> ct_degrees;
    ct_degrees.push_back(parent);
    for (int curr_degree = 1; curr_degree < degree; ++curr_degree) {
        CtOp* monomial;
        if (curr_degree == 1) {
            monomial = parent;
        } else {
            int nearest_pow2 = get_nearest_pow2(curr_degree - 1);
            monomial = ct_graph.mul(ct_degrees[nearest_pow2],
                                    ct_degrees[curr_degree - nearest_pow2]);
        }
        ct_degrees.push_back(monomial);
        auto post_mul = ct_graph.mul_pt(monomial);
        result = ct_graph.add(result, post_mul);
    }
    return result;
}

CtOp* first_poly(CtGraph& ct_graph, CtOp* parent) {
    return poly_eval(ct_graph, parent, 16);
}

CtOp* second_poly(CtGraph& ct_graph, CtOp* parent) {
    return poly_eval(ct_graph, parent, 7);
}

CtOp* third_poly(CtGraph& ct_graph, CtOp* parent) {
    return poly_eval(ct_graph, parent, 7);
}

CtOp* relu_function(CtGraph& ct_graph, CtOp* parent) {
    auto result = third_poly(
        ct_graph, second_poly(ct_graph, first_poly(ct_graph, parent)));
    return result;
}

CtTensor ReLU::cipherfy(CtGraph& ct_graph,
                        std::vector<CtTensor> parents) const {
    std::vector<CtOp*> result;
    auto parent_cts = parents[0].get_ct_ops();
    for (auto& ct_op : parent_cts) {
        auto ct_result = relu_function(ct_graph, ct_op);
        result.push_back(ct_result);
    }
    return CtTensor(result);
}
