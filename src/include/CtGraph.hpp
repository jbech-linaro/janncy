#ifndef CTGRAPH_HPP_
#define CTGRAPH_HPP_

#include "CtOp.hpp"
#include "Graph.hpp"

#include <vector>

class CtGraphVisitor;

class CtGraph : public Graph<CtOp> {
  public:
    CtGraph(){};
    // TODO(nsamar): Make cipherfy() const
    std::vector<std::vector<double>> evaluate(
        std::vector<std::vector<double>> init_values);
};

#endif  // CTGRAPH_HPP_
