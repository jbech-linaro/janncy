#ifndef CONVLAYER_HPP_
#define CONVLAYER_HPP_

#include <vector>

#include "FlowNode.hpp"
#include "KernelAttributes.hpp"

namespace janncy {

class FlowVisitor;

class ConvLayer : public FlowNode {
  public:
    ConvLayer(std::vector<int> input_shape,
              KernelAttributes kernel, int output_ch);

    void accept(FlowVisitor& visitor) override;
    std::string op_type() const override;
    std::vector<int> shape() const override;

    const KernelAttributes& kernel() const;
  private:
    KernelAttributes kernel_;
    std::vector<int> output_shape_;
};

}  // namespace janncy

#endif  // CONVLAYER_HPP_
