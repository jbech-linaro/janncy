#ifndef CTINPUT_HPP_
#define CTINPUT_HPP_

#include "CtOp.hpp"

#include <string>
#include <vector>

class CtGraphVisitor;
template <class T> class Graph;

class CtInput : public CtOp {
  public:
    CtInput();

    void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;
};

#endif  // CTINPUT_HPP_
