#ifndef FLATTEN_HPP_
#define FLATTEN_HPP_

#include "FlowNode.hpp"

namespace janncy {

class FlowVisitor;

class Flatten : public FlowNode {
  public:
    Flatten(const std::vector<int> &input_shape);

    void accept(FlowVisitor& visitor) override;
    std::string op_type() const override;
    std::vector<int> shape() const override;

  private:
    int output_dim_;
};

}  // namespace janncy

#endif  // FLATTEN_HPP_
