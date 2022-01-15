#include "include/KernelAttributes.hpp"

#include <algorithm>
#include <utility>
#include <vector>

#include "include/Panic.hpp"

KernelAttributes::KernelAttributes(std::vector<int> kernel_shape,
                                   std::vector<int> strides,
                                   std::vector<int> pads)
    : kernel_shape_(std::move(kernel_shape)), strides_(std::move(strides)) {
  int dims = kernel_shape_.size();

  if (strides_.empty()) {
    strides_ = std::vector<int>(dims, 1);
  }
  PANIC_IF(strides_.size() != kernel_shape_.size(), "Incompatible strides",
           strides_, kernel_shape_);

  if (pads.empty()) {
    begin_pads_ = std::vector<int>(dims, 0);
    end_pads_ = std::vector<int>(dims, 0);
  } else if (pads.size() == dims) {
    begin_pads_ = pads;
    end_pads_ = pads;
  } else if (pads.size() == 2 * dims) {
    auto pads_mid = pads.begin() + dims;
    begin_pads_ = std::vector<int>(pads.begin(), pads_mid);
    end_pads_ = std::vector<int>(pads.begin(), pads_mid);
  } else {
    PANIC("Incompatible pads", pads, kernel_shape_);
  }
}

const std::vector<int>& KernelAttributes::kernel_shape() const {
  return kernel_shape_;
}
const std::vector<int>& KernelAttributes::strides() const { return strides_; }
const std::vector<int>& KernelAttributes::begin_pads() const {
  return begin_pads_;
}
const std::vector<int>& KernelAttributes::end_pads() const { return end_pads_; }

std::vector<int> KernelAttributes::output_shape(
    const std::vector<int>& input_shape, int output_channels) const {
  PANIC_IF(input_shape.size() != kernel_shape_.size() + 1,
           "Incompatible input and kernel shapes", input_shape, kernel_shape_);

  std::vector<int> shape(input_shape.size());
  shape[0] = output_channels;
  for (int i = 0; i < kernel_shape_.size(); i++) {
    // From https://pytorch.org/docs/1.10.1/generated/torch.nn.Conv2d.html
    int padded_size = input_shape[i + 1] + begin_pads_[i] + end_pads_[i];
    PANIC_IF(padded_size < kernel_shape_[i]);
    shape[i + 1] = 1 + (padded_size - kernel_shape_[i]) / strides_[i];
  }
  return shape;
}
std::vector<int> KernelAttributes::output_shape(
    const std::vector<int>& input_shape) const {
  return output_shape(input_shape, input_shape[0]);
}
