#ifndef CTOP_HPP_
#define CTOP_HPP_

#include "Node.hpp"

#include <string>
#include <vector>

template <class T> class Graph;

class CtOp : public Node<CtOp> {
  public:
    explicit CtOp(std::vector<CtOp*> parents) : Node(parents) {}
    explicit CtOp(Graph<CtOp>* graph) : Node(graph) {}
    virtual std::string type_str() const = 0;
    std::string str() const;
};

#endif  // CTOP_HPP_
