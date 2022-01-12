#ifndef CONVLAYER_HPP_
#define CONVLAYER_HPP_

#include "FlowNode.hpp"

#include <vector>

namespace janncy {

class FlowVisitor;
class Flow;

class ConvLayer : public FlowNode {
  public:
    ConvLayer(std::vector<int> output_shape, std::vector<int> kernel_shape,
              std::vector<int> stride, std::vector<int> padding);

    void visit(Flow* flow, FlowVisitor* visitor);

    std::vector<int> stride() const;
    std::vector<int> padding() const;
    std::vector<int> kernel_shape() const;

  private:
    std::vector<int> kernel_shape_;
    std::vector<int> stride_;
    std::vector<int> padding_;
};

}  // namespace janncy

#endif  // CONVLAYER_HPP_
