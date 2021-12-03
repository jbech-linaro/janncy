#include "include/FullyConnected.hpp"

FullyConnected::FullyConnected(FlowNode* parent, Tensor matrix)
    : FlowNode({parent}, Tensor({matrix.shape()[1]})) {
}
