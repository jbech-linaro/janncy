#ifndef CTOP_HPP_
#define CTOP_HPP_

#include <string>
#include <vector>

namespace janncy {

template <class T> class Graph;

class CtGraph;
class CtGraphVisitor;

class CtOp {
  public:
    CtOp(std::string type_str);
    virtual ~CtOp() {};

    virtual void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) = 0;
    std::string str() const;

  private:
    std::string type_str_;
};

}  // namespace janncy

#endif  // CTOP_HPP_
