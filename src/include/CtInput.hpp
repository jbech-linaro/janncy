#ifndef CTINPUT_HPP_
#define CTINPUT_HPP_

#include "CtOp.hpp"

#include <string>
#include <vector>

template <class T> class Graph;

class CtInput : public CtOp {
  public:
    CtInput(Graph<CtOp>* graph) : CtOp(graph){};
    std::string type_str() const { return "CtInput"; }
};

#endif  // CTINPUT_HPP_
