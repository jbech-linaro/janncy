#include "include/ConvLayer.hpp"

#include "include/CtGraph.hpp"
#include "include/FlowNode.hpp"
#include "include/Tensor.hpp"
#include "include/utils.hpp"

#include <iostream>

ConvLayer::ConvLayer(FlowNode* parent, Tensor filter, int stride, bool padded)
    : FlowNode({parent},
               Tensor({filter.shape()[0],
                       get_output_width(parent, filter, stride, padded),
                       get_output_height(parent, filter, stride, padded)})),
      stride_(stride),
      filter_(filter),
      padded_(padded) {}

int ConvLayer::stride() const { return stride_; }

bool ConvLayer::padded() const { return padded_; }

Tensor ConvLayer::output_tensor() const { return output_tensor_; }

CtTensor ConvLayer::cipherfy(CtGraph& ct_graph,
                             std::vector<CtTensor> parents) const {
    auto parent = parents[0].get_ct_ops();
    auto result = std::vector<CtOp*>(output_tensor().shape()[0], nullptr);

    for (auto output_channel_idx = 0;
         output_channel_idx < output_tensor().shape()[0];
         ++output_channel_idx) {
        for (auto input_channel_idx = 0ul; input_channel_idx < parent.size();
             ++input_channel_idx) {
            for (auto filter_width_idx = 0;
                 filter_width_idx < filter_.shape()[1]; ++filter_width_idx) {
                for (auto filter_height_idx = 0;
                     filter_height_idx < filter_.shape()[1];
                     ++filter_height_idx) {
                    auto rot = ct_graph.rotate(parent[input_channel_idx]);
                    auto tmp = ct_graph.mul_pt(rot);
                    if (result[output_channel_idx]) {
                        result[output_channel_idx] =
                            ct_graph.add(result[output_channel_idx], tmp);
                    } else {
                        result[output_channel_idx] = tmp;
                    }
                }
            }
        }
    }
    return CtTensor(result);
}
