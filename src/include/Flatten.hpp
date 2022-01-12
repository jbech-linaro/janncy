#ifndef FLATTEN_HPP_
#define FLATTEN_HPP_

#include "FlowNode.hpp"

namespace janncy {

class FlowVisitor;
class Flow;

class Flatten : public FlowNode {
  public:
    Flatten(std::vector<int> output_shape);

    void visit(Flow* flow, FlowVisitor* visitor);
};

}  // namespace janncy

#endif  // FLATTEN_HPP_
