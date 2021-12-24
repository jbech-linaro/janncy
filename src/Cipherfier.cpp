#include "include/Cipherfier.hpp"

#include "include/ct_graph_utils.hpp"

#include "include/Add.hpp"
#include "include/AveragePool.hpp"
#include "include/BatchNormalization.hpp"
#include "include/ConvLayer.hpp"
#include "include/CtAdd.hpp"
#include "include/CtGraph.hpp"
#include "include/CtInput.hpp"
#include "include/CtMul.hpp"
#include "include/CtPtAdd.hpp"
#include "include/CtPtMul.hpp"
#include "include/CtRotate.hpp"
#include "include/CtTensor.hpp"
#include "include/Flatten.hpp"
#include "include/Flow.hpp"
#include "include/FlowNode.hpp"
#include "include/FullyConnected.hpp"
#include "include/Input.hpp"
#include "include/MaxPool.hpp"
#include "include/Panic.hpp"
#include "include/ReLU.hpp"

#include <unordered_map>

Cipherfier::Cipherfier() { ct_graph_ = new CtGraph(); };

void Cipherfier::register_node(const FlowNode* node,
                               const std::vector<CtOp*>& ct_ops) {
    ct_map_.insert(std::make_pair(node, CtTensor(ct_ops)));
}

template <class T>
CtAdd* accumulate(CtGraph* ct_graph, const std::vector<T*>& cts) {
    if (cts.size() == 2) {
        return ct_add(ct_graph, cts[0], cts[1]);
    }
    return ct_add(
        ct_graph, cts[0],
        accumulate(ct_graph, std::vector<CtOp*>(cts.begin() + 1, cts.end())));
}

template <class T> std::vector<CtOp*> create_many(int amt, T* obj) {
    auto result = std::vector<CtOp*>(amt, nullptr);
    result[0] = obj;
    std::transform(result.begin() + 1, result.end(), result.begin() + 1,
                   [&](auto x) {
                       (void)x;
                       return new T(*obj);
                   });
    return result;
}

std::vector<CtOp*> pt_mul(CtGraph* ct_graph, const std::vector<CtOp*>& cts) {
    auto multiplied = std::vector<CtOp*>();
    std::transform(cts.begin(), cts.end(), std::back_inserter(multiplied),
                   [&](auto& x) { return ct_pt_mul(ct_graph, x); });
    return multiplied;
}

CtTensor Cipherfier::ct_op(const FlowNode* node) {
    if (ct_map_.find(node) == ct_map_.end()) {
        return CtTensor({});
    }
    return ct_map_.at(node);
}

std::vector<CtTensor> Cipherfier::parents(Flow* flow, FlowNode* node) {
    auto prnts = flow->parents(node);
    auto result = std::vector<CtTensor>();
    std::transform(prnts.begin(), prnts.end(), std::back_inserter(result),
                   [&](auto& x) { return ct_op(x); });
    return result;
}

CtAdd* apply_filter(CtGraph* ct_graph, const std::vector<CtOp*>& parents,
                    int filter_size) {
    auto filtered_channels = std::vector<CtOp*>();
    std::transform(
        parents.begin(), parents.end(), std::back_inserter(filtered_channels),
        [&](auto& p) {
            return accumulate(
                ct_graph,
                pt_mul(ct_graph,
                       create_many(filter_size, ct_rotate(ct_graph, p))));
        });
    return accumulate(ct_graph, filtered_channels);
}

void Cipherfier::visit(Flow* flow, ConvLayer* node) {
    auto parent = parents(flow, node)[0].get_ct_ops();
    auto output_channels = node->shape()[0];
    auto filter_size = node->kernel_shape()[1] * node->kernel_shape()[1];
    auto result = create_many(output_channels,
                              apply_filter(ct_graph_, parent, filter_size));
    register_node(node, result);
}

void Cipherfier::visit(Flow* flow, FullyConnected* node) {
    auto parent = parents(flow, node)[0].get_ct_ops();
    auto result = create_many(node->shape()[0],
                              accumulate(ct_graph_, pt_mul(ct_graph_, parent)));
    register_node(node, result);
}

void Cipherfier::visit(Flow* flow, MaxPool* node) {
    // TODO(nsamar): this node is currently just bypassed
    register_node(node, parents(flow, node)[0].get_ct_ops());
}

void Cipherfier::visit(Flow* flow, Flatten* node) {
    // TODO(nsamar): this node is currently just bypassed
    register_node(node, parents(flow, node)[0].get_ct_ops());
}

void Cipherfier::visit(Flow* flow, AveragePool* node) {
    auto parent = parents(flow, node)[0].get_ct_ops();
    auto result = std::vector<CtOp*>();
    auto amt = log2(node->kernel_shape()[1]);
    std::transform(
        parent.begin(), parent.end(), std::back_inserter(result), [&](auto x) {
            return accumulate(ct_graph_,
                              create_many(amt, ct_rotate(ct_graph_, x)));
        });
    std::transform(parent.begin(), parent.end(), result.begin(), [&](auto x) {
        return accumulate(ct_graph_, create_many(amt, ct_rotate(ct_graph_, x)));
    });
    register_node(node, result);
}

void Cipherfier::visit(Flow* flow, BatchNormalization* node) {
    auto parent = parents(flow, node)[0].get_ct_ops();
    std::vector<CtOp*> result;
    std::transform(
        parent.begin(), parent.end(), std::back_inserter(result),
        [&](auto x) { return ct_pt_mul(ct_graph_, ct_pt_add(ct_graph_, x)); });
    register_node(node, result);
}

void Cipherfier::visit(Flow* flow, Add* node) {
    auto p0 = parents(flow, node)[0].get_ct_ops();
    auto p1 = parents(flow, node)[1].get_ct_ops();
    std::vector<CtOp*> result;
    std::transform(p0.begin(), p0.end(), p1.begin(), std::back_inserter(result),
                   [&](auto x, auto y) { return ct_add(ct_graph_, x, y); });
    register_node(node, result);
}

void Cipherfier::visit(Flow* flow, Input* node) {
    auto result = create_many(node->shape()[0], new CtInput());
    register_node(node, result);
}

std::vector<CtOp*> get_exponents(CtGraph* ct_graph, CtOp* ct, int degree) {
    if (degree == 1) {
        return {ct};
    }
    auto exponents = get_exponents(ct_graph, ct, degree / 2);
    auto exponent_degree_half = *(exponents.end() - 1);
    auto remaining_exponents = std::vector<CtOp*>();
    std::transform(exponents.begin(), exponents.end(),
                   std::back_inserter(remaining_exponents), [&](auto& x) {
                       return ct_mul(ct_graph, exponent_degree_half, x);
                   });
    exponents.insert(exponents.end(),
                     std::make_move_iterator(remaining_exponents.begin()),
                     std::make_move_iterator(remaining_exponents.end()));
    if (degree % 2 == 1) {
        exponents.push_back(ct_mul(ct_graph, ct, *(exponents.end() - 1)));
    }
    return exponents;
}

CtOp* poly_eval(CtGraph* ct_graph, CtOp* parent, int degree) {
    auto exponents = get_exponents(ct_graph, parent, degree);
    auto multiplied_exponents = pt_mul(ct_graph, exponents);
    return accumulate(ct_graph, multiplied_exponents);
}

CtOp* first_poly(CtGraph* ct_graph, CtOp* parent) {
    return poly_eval(ct_graph, parent, 16);
}

CtOp* second_poly(CtGraph* ct_graph, CtOp* parent) {
    return poly_eval(ct_graph, parent, 7);
}

CtOp* third_poly(CtGraph* ct_graph, CtOp* parent) {
    return poly_eval(ct_graph, parent, 7);
}

CtOp* relu_function(CtGraph* ct_graph, CtOp* parent) {
    auto result = third_poly(
        ct_graph, second_poly(ct_graph, first_poly(ct_graph, parent)));
    return result;
}

void Cipherfier::visit(Flow* flow, ReLU* node) {
    std::vector<CtOp*> result;
    auto parent_cts = parents(flow, node)[0].get_ct_ops();
    std::transform(parent_cts.begin(), parent_cts.end(),
                   std::back_inserter(result),
                   [&](auto& x) { return relu_function(ct_graph_, x); });
    register_node(node, result);
}
