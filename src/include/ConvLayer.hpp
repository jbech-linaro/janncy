#ifndef CONVLAYER_HPP_
#define CONVLAYER_HPP_

#include "FlowNode.hpp"
#include "Tensor.hpp"

class FlowVisitor;

class ConvLayer : public FlowNode {
  public:
    static ConvLayer* create(FlowNode* parent, Tensor filter, int stride,
                             bool padding) {
        return new ConvLayer(parent, filter, stride, padding);
    };
    void visit(FlowVisitor* visitor);
    Tensor filter() const;
    int stride() const;
    int padding() const;
    std::string type_str() const { return "ConvLayer"; }

  private:
    ConvLayer(FlowNode* parent, Tensor filter, int stride, int padding);
    int stride_;
    Tensor filter_;
    int padding_;
};

#endif  // CONVLAYER_HPP_
