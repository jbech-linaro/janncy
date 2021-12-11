#ifndef CTOP_HPP_
#define CTOP_HPP_

#include "Node.hpp"

#include <string>
#include <vector>

template <class T> class Graph;

class CtGraphVisitor;

class CtOp : public Node<CtOp> {
  public:
    explicit CtOp(std::vector<CtOp*> parents) : Node(parents) {}
    explicit CtOp(Graph<CtOp>* graph) : Node(graph) {}
    virtual std::string type_str() const = 0;
    virtual void visit(CtGraphVisitor* visitor) = 0;
    std::string str() const;
};

#endif  // CTOP_HPP_
