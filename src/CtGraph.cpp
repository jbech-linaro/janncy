#include "include/CtGraph.hpp"

#include "include/CtInput.hpp"
#include "include/CtOp.hpp"
#include "include/CtTensor.hpp"
#include "include/FlowNode.hpp"

#include <vector>

CtTensor CtGraph::input(FlowNode* input_node) {
    std::vector<CtOp*> result;
    for (int i = 0; i < input_node->output_tensor().shape()[0]; ++i) {
        result.push_back(new CtInput(this));
    }
    return CtTensor(result);
}
