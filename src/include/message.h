#ifndef JANNCY_MESSAGE_H_
#define JANNCY_MESSAGE_H_

#include <memory>
#include <vector>

#include "include/chunk_layout.h"
#include "include/weight_manager.h"

namespace janncy {

class Message {
 public:
  using Scalar = double;
  using Vector = std::vector<Scalar>;

  Message() = default;
  Message(Message&&) = default;
  virtual ~Message() {}
  Message(const Message&) = delete;
  Message& operator=(const Message&) = delete;
  Message& operator=(const Message&&) = default;

  virtual Vector Evaluate(const WeightManager& wm) const = 0;
};

class Scalar : public Message {
 public:
  Scalar(Message::Scalar scalar) : scalar_(scalar){};
  Message::Vector Evaluate(const WeightManager&) const override {
    return {scalar_};
  }

 private:
  Message::Scalar scalar_;
};

class WeightMessage : public Message {
 public:
  WeightMessage(std::string weight_id, ChunkLayout chunk_layout,
                std::vector<int> offset)
      : weight_id_(weight_id), chunk_layout_(chunk_layout), offset_(offset) {}

  Message::Vector Evaluate(const WeightManager& wm) const override;

 private:
  std::string weight_id_;
  ChunkLayout chunk_layout_;
  std::vector<int> offset_;
};

class ReplicatedMessage : public Message {
 public:
  ReplicatedMessage(std::unique_ptr<Message> input_message,
                    ChunkMask chunk_mask)
      : input_(std::move(input_message)), chunk_mask_(chunk_mask) {}

  Message::Vector Evaluate(const WeightManager& wm) const override;

 private:
  std::unique_ptr<Message> input_;
  ChunkMask chunk_mask_;
};

class RotatedMessage : public Message {
 public:
  RotatedMessage(std::unique_ptr<Message> input_message, int rotation_amount)
      : input_(std::move(input_message)), rotation_amount_(rotation_amount) {}

  Message::Vector Evaluate(const WeightManager&) const override;

 private:
  std::unique_ptr<Message> input_;
  int rotation_amount_;
};

class MaskedMessage : public Message {
 public:
  MaskedMessage(std::unique_ptr<Message> input_message, ChunkMask chunk_mask)
      : input_(std::move(input_message)), chunk_mask_(chunk_mask) {}

  Message::Vector Evaluate(const WeightManager&) const override;

 private:
  std::unique_ptr<Message> input_;
  ChunkMask chunk_mask_;
};

class AddedMessage : public Message {
 public:
  AddedMessage(std::unique_ptr<Message> input0, std::unique_ptr<Message> input1)
      : input0_(std::move(input0)), input1_(std::move(input1)) {}

  Message::Vector Evaluate(const WeightManager&) const override;

 private:
  std::unique_ptr<Message> input0_;
  std::unique_ptr<Message> input1_;
};

}  // namespace janncy

#endif  // JANNCY_MESSAGE_H_
