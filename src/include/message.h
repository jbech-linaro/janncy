#ifndef JANNCY_MESSAGE_H_
#define JANNCY_MESSAGE_H_

#include <vector>

namespace janncy {

class Message {
 public:
  using Scalar = double;
  using Vector = std::vector<Scalar>;
  explicit Message(Vector message_vec) : message_vec_(message_vec) {}
  Vector message_vec() const { return message_vec_; }

 private:
  Vector message_vec_;
};

}  // namespace janncy

#endif  // JANNCY_MESSAGE_H_
