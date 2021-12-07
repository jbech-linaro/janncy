#include "include/Input.hpp"

#include "include/CtGraph.hpp"

#include <cassert>
#include <iostream>

Input::Input(Tensor input_tensor) : FlowNode({}, input_tensor) {}

CtTensor Input::cipherfy(CtGraph& ct_graph,
                         std::vector<CtTensor> parents) const {
    assert(parents.size() == 0);
    std::vector<CtOp*> in_vec;
    for (auto i = 0; i < output_tensor().shape()[0]; ++i) {
        in_vec.push_back(ct_graph.input());
    }
    auto result = CtTensor(in_vec);
    return result;
}
