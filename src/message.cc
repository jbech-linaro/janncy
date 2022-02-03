#include "include/message.h"

#include <vector>

#include "include/chunk_layout.h"

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

Message::Vector ReplicateMessage(const Message::Vector& message,
                                 const ChunkMask& chunk_mask) {
  ChunkMask keep_mask = chunk_mask;
  keep_mask.flip();
  Message::Vector result;
  result.reserve(message.size());
  for (int idx = 0; idx < message.size(); ++idx) {
    result.push_back(message[idx & keep_mask.to_ulong()]);
  }
  return message;
}

Message::Vector RotateMessage(const Message::Vector& message,
                              int rotation_amount) {
  Message::Vector result = message;
  std::rotate(result.begin(), result.begin() + rotation_amount, result.end());
  return result;
}

Message::Vector MaskMessage(const Message::Vector& message,
                            const ChunkMask& chunk_mask) {
  Message::Vector result;
  result.reserve(message.size());
  for (int idx = 0; idx < message.size(); ++idx) {
    if (idx & chunk_mask == chunk_mask) {
      result.push_back(0);
    } else {
      result.push_back(message[idx]);
    }
  }
  return result;
}

}  // namespace

Message::Vector WeightMessage::Evaluate(const WeightManager& wm) const {
  Tensor input_message = wm.weight(weight_id_);
  return TensorToMessageVector(input_message, chunk_layout_, offset_);
}

Message::Vector ReplicatedMessage::Evaluate(const WeightManager& wm) const {
  auto input_message = input_->Evaluate(wm);
  return ReplicateMessage(input_message, chunk_mask_);
}

Message::Vector RotatedMessage::Evaluate(const WeightManager& wm) const {
  auto input_message = input_->Evaluate(wm);
  return RotateMessage(input_message, rotation_amount_);
}

Message::Vector MaskedMessage::Evaluate(const WeightManager& wm) const {
  auto input_message = input_->Evaluate(wm);
  return MaskMessage(input_message, chunk_mask_);
}

Message::Vector AddedMessage::Evaluate(const WeightManager& wm) const {
  auto input0 = input0_->Evaluate(wm);
  auto input1 = input1_->Evaluate(wm);
  Message::Vector result;
  result.reserve(input0.size());
  std::transform(input0.begin(), input0.end(), input1.begin(),
                 std::back_inserter(result), std::plus<Message::Scalar>());
  return result;
}

}  // namespace janncy
