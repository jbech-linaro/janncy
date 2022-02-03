#include "include/message.h"

#include <vector>

namespace janncy {

namespace {

std::vector<std::vector<std::optional<int>>> TensorIndices(
    const ChunkLayout& layout, const std::vector<int>& offset) {
  std::vector<std::vector<std::optional<int>>> result;
  result.reserve(offset.size());
  for (int dim_idx = 0; dim_idx < offset.size(); ++dim_idx) {
    result.push_back(layout.DimensionIndices(dim_idx, offset[dim_idx]));
  }
  return result;
}

std::optional<std::vector<int>> ReadIndex(
    const std::vector<std::vector<std::optional<int>>>& tensor_indices,
    int index) {
  int dimension_count = tensor_indices.size();
  std::vector<int> result;
  if (!tensor_indices[0][index].has_value()) {
    return std::nullopt;
  }
  for (int i = 0; i < dimension_count; ++i) {
    result.push_back(tensor_indices[i][index].value());
  }
  return std::optional{result};
}

Message::Scalar TensorAt(const Tensor& tensor,
                         std::optional<std::vector<int>> tensor_idx) {
  if (!tensor_idx.has_value()) {
    return 0;
  }
  return tensor.at(tensor_idx.value());
}

Message::Vector TensorToMessageVector(const Tensor& tensor,
                                      const ChunkLayout& layout,
                                      const std::vector<int>& offset) {
  std::vector<std::vector<std::optional<int>>> tensor_indices =
      TensorIndices(layout, offset);
  int chunk_size = tensor_indices[0].size();
  Message::Vector result;
  result.reserve(chunk_size);
  for (int i = 0; i < chunk_size; ++i) {
    auto tensor_idx = ReadIndex(tensor_indices, i);
    result.push_back(TensorAt(tensor, tensor_idx));
  }
  return result;
}

}  // namespace

Message::Vector WeightMessage::Evaluate(const WeightManager& wm) const {
  Tensor input_message = wm.weight(weight_id_);
  return TensorToMessageVector(input_message, chunk_layout_, offset_);
}

}  // namespace janncy
