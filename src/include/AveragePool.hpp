#ifndef AVERAGEPOOL_HPP_
#define AVERAGEPOOL_HPP_

#include "Tensor.hpp"
#include "FlowNode.hpp"

class AveragePool : public FlowNode {
public:
    AveragePool(FlowNode* parent, Tensor pool, int stride);
    int stride() const;
    std::string type_str() const { return "AveragePool"; }
private:
    int stride_;
};

#endif  // AVERAGEPOOL_HPP_
