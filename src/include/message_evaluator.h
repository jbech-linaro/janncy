#ifndef JANNCY_MESSAGE_EVALUATOR_H_
#define JANNCY_MESSAGE_EVALUATOR_H_

#include "include/message.h"

namespace janncy {

class MessageEvaluator {
 public:
  MessageEvaluator() = default;
  Message::Vector evaluate(Message* message) { return message->message_vec(); }
};

}  // namespace janncy

#endif  // JANNCY_MESSAGE_EVALUATOR_H_
