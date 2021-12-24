#ifndef CTPTADD_HPP_
#define CTPTADD_HPP_

#include "CtOp.hpp"

#include <string>
#include <vector>

class CtGraphVisitor;

class CtPtAdd : public CtOp {
  public:
    CtPtAdd();

    std::vector<double> value() const;

    void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;

  private:
    std::vector<double> value_;
};

#endif  // CTPTADD_HPP_
