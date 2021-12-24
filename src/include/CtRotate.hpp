#ifndef CTROTATE_HPP_
#define CTROTATE_HPP_

#include "CtOp.hpp"

#include <string>

class CtGraphVisitor;

class CtRotate : public CtOp {
  public:
    CtRotate();

    int amt() const;

    void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;

  private:
    int amt_;
};

#endif  // CTROTATE_HPP_
