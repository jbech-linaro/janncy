#ifndef JANNCY_CT_OP_H_
#define JANNCY_CT_OP_H_

#include <string>
#include <vector>

namespace janncy {

template <class T>
class Graph;

class CtGraph;
class CtGraphVisitor;

class CtOp {
 public:
  CtOp(std::string type_str);
  virtual ~CtOp(){};

  virtual void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) = 0;
  std::string str() const;

 private:
  std::string type_str_;
};

}  // namespace janncy

#endif  // JANNCY_CT_OP_H_
