#ifndef FLOW_HPP_
#define FLOW_HPP_

#include "CtGraph.hpp"
#include "FlowNode.hpp"
#include "Graph.hpp"

#include <vector>

class Flow : public Graph<FlowNode> {
  public:
    FlowNode* input(Tensor input_tensor);
    FlowNode* conv_layer(FlowNode* parent, Tensor filter, int stride,
                         bool padded);
    FlowNode* reLU(FlowNode* parent);
    FlowNode* batch_normalization(FlowNode* parent);
    FlowNode* average_pool(FlowNode* parent, Tensor pool, int stride,
                           bool padded);
    FlowNode* fully_connected(FlowNode* parent, Tensor matrix);
    FlowNode* add(FlowNode* parent0, FlowNode* parent1);

    CtGraph cipherfy();
};

#endif  // FLOWNODE_HPP_
