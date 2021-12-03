#ifndef AVERAGEPOOL_HPP_
#define AVERAGEPOOL_HPP_

#include "Tensor.hpp"
#include "FlowNode.hpp"

class AveragePool : public FlowNode {
public:
    AveragePool(FlowNode* parent, Tensor pool, int stride, bool padded);
    int stride() const;
    bool padded() const;
    std::string type_str() const { return "AveragePool"; }
private:
    int stride_;
    bool padded_;
};

#endif  // AVERAGEPOOL_HPP_
