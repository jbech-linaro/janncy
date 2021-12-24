#ifndef CTADD_HPP_
#define CTADD_HPP_

#include "CtOp.hpp"

#include <string>

class CtGraphVisitor;

class CtAdd : public CtOp {
  public:
    CtAdd();

    void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;

  private:
};

#endif  // CTADD_HPP_
