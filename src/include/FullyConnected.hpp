#ifndef FULLYCONNECTED_HPP_
#define FULLYCONNECTED_HPP_

#include "FlowNode.hpp"

namespace janncy {

class FlowVisitor;

class FullyConnected : public FlowNode {
 public:
  FullyConnected(int input_size, int output_size);

  void accept(FlowVisitor& visitor) override;
  std::string op_type() const override;
  std::vector<int> shape() const override;

  int input_size() const;
  int output_size() const;

 private:
  int input_size_;
  int output_size_;
};

}  // namespace janncy

#endif  // FULLYCONNECTRED_HPP_
