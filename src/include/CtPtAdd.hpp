#ifndef CTPTADD_HPP_
#define CTPTADD_HPP_

#include <string>
#include <vector>

#include "CtOp.hpp"

namespace janncy {

class CtGraphVisitor;

class CtPtAdd : public CtOp {
 public:
  CtPtAdd();

  std::vector<double> value() const;

  void visit(CtGraph* ct_graph, CtGraphVisitor* visitor) override;

 private:
  std::vector<double> value_;
};

}  // namespace janncy

#endif  // CTPTADD_HPP_
