#ifndef JANNCY_MESSAGE_H_
#define JANNCY_MESSAGE_H_

#include <vector>

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

}  // namespace janncy

#endif  // JANNCY_MESSAGE_H_
