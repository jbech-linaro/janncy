#include "include/Cipherfier.hpp"

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
#include "include/FlowNode.hpp"
#include "include/FullyConnected.hpp"
#include "include/Input.hpp"
#include "include/Panic.hpp"
#include "include/ReLU.hpp"

#include <unordered_map>

Cipherfier::Cipherfier() { ct_graph_ = new CtGraph(); };

void Cipherfier::register_node(FlowNode* node, std::vector<CtOp*> ct_ops) {
    ct_map_.insert(std::make_pair(node, CtTensor(ct_ops)));
}

template <class T> CtAdd* accumulate(std::vector<T*> cts) {
    if (cts.size() == 2) {
        return CtAdd::create(cts[0], cts[1]);
    }
    return CtAdd::create(
        cts[0], accumulate(std::vector<CtOp*>(cts.begin() + 1, cts.end())));
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

std::vector<CtOp*> pt_mul(std::vector<CtOp*> cts) {
    auto multiplied = std::vector<CtOp*>();
    std::transform(cts.begin(), cts.end(), std::back_inserter(multiplied),
                   [&](auto& x) { return CtPtMul::create(x); });
    return multiplied;
}

CtTensor Cipherfier::ct_op(FlowNode* node) {
    if (ct_map_.find(node) == ct_map_.end()) {
        return CtTensor({ct_graph_->sentinel()});
    }
    return ct_map_.at(node);
}

std::vector<CtTensor> Cipherfier::parents(FlowNode* node) {
    // TODO: rename get_parents in Node to parents(). Same for children()
    auto prnts = node->get_parents();
    auto result = std::vector<CtTensor>();
    std::transform(prnts.begin(), prnts.end(), std::back_inserter(result),
                   [&](auto& x) { return ct_op(x); });
    return result;
}

CtAdd* apply_filter(std::vector<CtOp*> parents, int filter_size) {
    auto filtered_channels = std::vector<CtOp*>();
    std::transform(parents.begin(), parents.end(),
                   std::back_inserter(filtered_channels), [&](auto& p) {
                       return accumulate(pt_mul(
                           create_many(filter_size, CtRotate::create(p))));
                   });
    return accumulate(filtered_channels);
}

void Cipherfier::visit(ConvLayer* node) {
    auto parent = parents(node)[0].get_ct_ops();
    auto output_channels = node->shape()[0];
    auto filter_size = node->filter().shape()[1] * node->filter().shape()[1];
    auto result =
        create_many(output_channels, apply_filter(parent, filter_size));
    register_node(node, result);
}

void Cipherfier::visit(FullyConnected* node) {
    auto parent = parents(node)[0].get_ct_ops();
    auto result = create_many(node->shape()[0], accumulate(pt_mul(parent)));
    register_node(node, result);
}

void Cipherfier::visit(AveragePool* node) {
    auto parent = parents(node)[0].get_ct_ops();
    auto result = std::vector<CtOp*>();
    auto amt = log2(node->pool().shape()[1]);
    std::transform(parent.begin(), parent.end(), std::back_inserter(result),
                   [&](auto x) {
                       return accumulate(create_many(amt, CtRotate::create(x)));
                   });
    std::transform(parent.begin(), parent.end(), result.begin(), [&](auto x) {
        return accumulate(create_many(amt, CtRotate::create(x)));
    });
    register_node(node, result);
}

void Cipherfier::visit(BatchNormalization* node) {
    auto parent = parents(node)[0].get_ct_ops();
    std::vector<CtOp*> result;
    std::transform(parent.begin(), parent.end(), std::back_inserter(result),
                   [&](auto x) { return CtPtMul::create(CtPtAdd::create(x)); });
    register_node(node, result);
}

void Cipherfier::visit(Add* node) {
    auto p0 = parents(node)[0].get_ct_ops();
    auto p1 = parents(node)[1].get_ct_ops();
    std::vector<CtOp*> result;
    std::transform(p0.begin(), p0.end(), p1.begin(), std::back_inserter(result),
                   [&](auto x, auto y) { return CtAdd::create(x, y); });
    register_node(node, result);
}

void Cipherfier::visit(Input* node) {
    auto graph = parents(node)[0].get_ct_ops()[0]->graph();
    auto result = create_many(node->shape()[0], new CtInput(graph));
    register_node(node, result);
}

std::vector<CtOp*> get_exponents(CtOp* ct, int degree) {
    if (degree == 1) {
        return {ct};
    }
    auto exponents = get_exponents(ct, degree / 2);
    auto exponent_degree_half = *(exponents.end() - 1);
    auto remaining_exponents = std::vector<CtOp*>();
    std::transform(exponents.begin(), exponents.end(),
                   std::back_inserter(remaining_exponents), [&](auto& x) {
                       return CtMul::create(exponent_degree_half, x);
                   });
    exponents.insert(exponents.end(),
                     std::make_move_iterator(remaining_exponents.begin()),
                     std::make_move_iterator(remaining_exponents.end()));
    if (degree % 2 == 1) {
        exponents.push_back(CtMul::create(ct, *(exponents.end() - 1)));
    }
    return exponents;
}

CtOp* poly_eval(CtOp* parent, int degree) {
    auto exponents = get_exponents(parent, degree);
    auto multiplied_exponents = pt_mul(exponents);
    return accumulate(multiplied_exponents);
}

CtOp* first_poly(CtOp* parent) { return poly_eval(parent, 16); }

CtOp* second_poly(CtOp* parent) { return poly_eval(parent, 7); }

CtOp* third_poly(CtOp* parent) { return poly_eval(parent, 7); }

CtOp* relu_function(CtOp* parent) {
    auto result = third_poly(second_poly(first_poly(parent)));
    return result;
}

void Cipherfier::visit(ReLU* node) {
    std::vector<CtOp*> result;
    auto parent_cts = parents(node)[0].get_ct_ops();
    std::transform(parent_cts.begin(), parent_cts.end(),
                   std::back_inserter(result),
                   [&](auto& x) { return relu_function(x); });
    register_node(node, result);
}
