#ifndef BATCHNORMALIZATION_HPP_
#define BATCHNORMALIZATION_HPP_

#include "FlowNode.hpp"

class FlowVisitor;
class Flow;

namespace janncy {

class BatchNormalization : public FlowNode {
  public:
    BatchNormalization(std::vector<int> output_shape);

    void visit(Flow* flow, FlowVisitor* visitor);
};

}  // namespace janncy

#endif  // BATCHNORMALIZATION_HPP_
