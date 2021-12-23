#include "include/Flatten.hpp"

#include "include/FlowNode.hpp"
#include "include/FlowVisitor.hpp"
#include "include/Tensor.hpp"

#include <cassert>
#include <functional>
#include <numeric>

Tensor flatten(Tensor tensor, int axis) {
    assert(axis < tensor.shape().size());
    auto dim_vec = tensor.shape();
    auto first_dim = std::accumulate(dim_vec.begin(), dim_vec.begin() + axis, 1,
                                     std::multiplies<int>{});
    auto second_dim = std::accumulate(dim_vec.begin() + axis, dim_vec.end(), 1,
                                      std::multiplies<int>{});
    return Tensor({first_dim, second_dim});
}

Flatten::Flatten(FlowNode* parent, int axis)
    : FlowNode({parent}, flatten(parent->output_tensor(), axis)) {}

void Flatten::visit(FlowVisitor* visitor) { visitor->visit(this); }
