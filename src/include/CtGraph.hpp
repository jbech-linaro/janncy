#ifndef CTGRAPH_HPP_
#define CTGRAPH_HPP_

#include <vector>

#include "CtOp.hpp"
#include "Graph.hpp"

namespace janncy {

class CtGraphVisitor;

class CtGraph : public Graph<CtOp> {
 public:
  // TODO(nsamar): Make evaluate() and cipherfy() const
  // TODO(alex): Move this evaluate directly to the visitor class?
  std::vector<std::vector<double>> evaluate(
      std::vector<std::vector<double>> init_values);

  CtOp* create_input();
  CtOp* create_add(const CtOp* parent_1, const CtOp* parent_2);
  CtOp* create_mul(const CtOp* parent_1, const CtOp* parent_2);
  CtOp* create_pt_add(const CtOp* parent);
  CtOp* create_pt_mul(const CtOp* parent);
  CtOp* create_rotate(const CtOp* parent);
};

}  // namespace janncy

#endif  // CTGRAPH_HPP_
