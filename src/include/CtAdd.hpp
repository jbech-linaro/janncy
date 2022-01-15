#ifndef CTADD_HPP_
#define CTADD_HPP_

#include <string>

#include "CtOp.hpp"

namespace janncy {

class CtGraphVisitor;

class CtAdd : public CtOp {
 public:
  CtAdd();

  void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;

 private:
};

}  // namespace janncy

#endif  // CTADD_HPP_
