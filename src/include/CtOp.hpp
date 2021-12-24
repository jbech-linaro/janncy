#ifndef CTOP_HPP_
#define CTOP_HPP_

#include <string>
#include <vector>

template <class T> class Graph;

class CtGraph;
class CtGraphVisitor;

class CtOp {
  public:
    CtOp(std::string type_str);

    virtual void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) = 0;

    std::string str() const;

  private:
    std::string type_str_;
};

#endif  // CTOP_HPP_
