#ifndef CTINPUT_HPP_
#define CTINPUT_HPP_

#include "CtOp.hpp"

#include <string>
#include <vector>

class CtGraphVisitor;
template <class T> class Graph;

class CtInput : public CtOp {
  public:
    CtInput(Graph<CtOp>* graph) : CtOp(graph){};
    std::string type_str() const override { return "CtInput"; }
    void visit(CtGraphVisitor* visitor) override;
};

#endif  // CTINPUT_HPP_
