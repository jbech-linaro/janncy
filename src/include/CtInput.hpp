#ifndef CTINPUT_HPP_
#define CTINPUT_HPP_

#include <string>
#include <vector>

#include "CtOp.hpp"

namespace janncy {

class CtGraphVisitor;
template <class T>
class Graph;

class CtInput : public CtOp {
 public:
  CtInput();

  void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;
};

}  // namespace janncy

#endif  // CTINPUT_HPP_
