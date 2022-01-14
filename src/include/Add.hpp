#ifndef ADD_HPP_
#define ADD_HPP_

#include <vector>

#include "FlowNode.hpp"

namespace janncy {

class FlowVisitor;

class Add : public FlowNode {
  public:
    Add(std::vector<int> shape);

    void accept(FlowVisitor& visitor) override;
    std::vector<int> shape() const override;
    std::string op_type() const override;

  private:
    std::vector<int> shape_;
};

}  // namespace janncy

#endif  // ADD_HPP_
