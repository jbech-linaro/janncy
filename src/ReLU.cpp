#include "include/ReLU.hpp"

#include "include/CtAdd.hpp"
#include "include/CtGraph.hpp"
#include "include/CtMul.hpp"
#include "include/CtPtMul.hpp"
#include "include/FlowNode.hpp"

#include <iostream>

ReLU::ReLU(FlowNode* parent)
    : FlowNode({parent}, parent->output_tensor(), parent->flow()) {}

int get_nearest_pow2(int n) {
    if (n == 1) {
        return 1;
    }
    return 2 * get_nearest_pow2(n >> 1);
}

CtOp* poly_eval(CtOp* parent, int degree) {
    auto result = parent;
    std::vector<CtOp*> ct_degrees;
    ct_degrees.push_back(parent);
    for (int curr_degree = 1; curr_degree < degree; ++curr_degree) {
        CtOp* monomial;
        if (curr_degree == 1) {
            monomial = parent;
        } else {
            int nearest_pow2 = get_nearest_pow2(curr_degree - 1);
            monomial = CtMul::create(ct_degrees[nearest_pow2],
                                     ct_degrees[curr_degree - nearest_pow2]);
        }
        ct_degrees.push_back(monomial);
        auto post_mul = CtPtMul::create(monomial);
        result = CtAdd::create(result, post_mul);
    }
    return result;
}

CtOp* first_poly(CtOp* parent) { return poly_eval(parent, 16); }

CtOp* second_poly(CtOp* parent) { return poly_eval(parent, 7); }

CtOp* third_poly(CtOp* parent) { return poly_eval(parent, 7); }

CtOp* relu_function(CtOp* parent) {
    auto result = third_poly(second_poly(first_poly(parent)));
    return result;
}

CtTensor ReLU::cipherfy(std::vector<CtTensor> parents) const {
    std::vector<CtOp*> result;
    auto parent_cts = parents[0].get_ct_ops();
    for (auto& ct_op : parent_cts) {
        auto ct_result = relu_function(ct_op);
        result.push_back(ct_result);
    }
    return CtTensor(result);
}
