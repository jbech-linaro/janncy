#ifndef CTADD_HPP_
#define CTADD_HPP_

#include "CtOp.hpp"

#include <string>

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
