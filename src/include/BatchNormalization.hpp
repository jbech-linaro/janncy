#ifndef BATCHNORMALIZATION_HPP_
#define BATCHNORMALIZATION_HPP_

#include "FlowNode.hpp"

class FlowVisitor;
class Flow;

namespace janncy {

class BatchNormalization : public FlowNode {
  public:
    BatchNormalization(std::vector<int> shape);

    void accept(FlowVisitor& visitor) override;
    std::string op_type() const override;
    std::vector<int> shape() const override;

  private:
    std::vector<int> shape_;
};

}  // namespace janncy

#endif  // BATCHNORMALIZATION_HPP_
