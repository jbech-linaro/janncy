#ifndef CTROTATE_HPP_
#define CTROTATE_HPP_

#include <string>

#include "CtOp.hpp"

namespace janncy {

class CtGraphVisitor;

class CtRotate : public CtOp {
 public:
  CtRotate();

  int amt() const;

  void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;

 private:
  int amt_;
};

}  // namespace janncy

#endif  // CTROTATE_HPP_
