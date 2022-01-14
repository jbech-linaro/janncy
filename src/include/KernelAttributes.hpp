#ifndef KERNELATTRIBUTES_HPP
#define KERNELATTRIBUTES_HPP

#include <vector>

class KernelAttributes {
  public:
    // `kernel_shape` includes only the spacial dimensions of the kernel,
    //                i.e, it must have the same number of dimensions as
    //                `stride` and `padding`.
    // `stride` defaults to `1` along all dimensions
    // `padding` defaults to `0` along all dimensions
    KernelAttributes(std::vector<int> kernel_shape,
                     std::vector<int> strides = {},
                     std::vector<int> pads = {});

    int dim_cnt() const;
    const std::vector<int>& kernel_shape() const;
    const std::vector<int>& strides() const;
    const std::vector<int>& begin_pads() const;
    const std::vector<int>& end_pads() const;

    std::vector<int> output_shape(const std::vector<int> &input_shape,
                                  int output_channels) const;
    std::vector<int> output_shape(const std::vector<int> &input_shape) const;

  private:
    std::vector<int> kernel_shape_;
    std::vector<int> strides_;
    std::vector<int> begin_pads_;
    std::vector<int> end_pads_;
};

#endif  // KERNELATTRIBUTES_HPP
