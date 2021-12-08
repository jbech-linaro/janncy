#ifndef CTADD_HPP_
#define CTADD_HPP_

#include "CtOp.hpp"

#include <string>

class CtAdd : public CtOp {
  public:
    static CtAdd* create(CtOp* parent0, CtOp* parent1) {
        return new CtAdd(parent0, parent1);
    }
    std::string type_str() const { return "CtAdd"; }

  private:
    CtAdd(CtOp* parent0, CtOp* parent1) : CtOp({parent0, parent1}){};
};

#endif  // CTADD_HPP_
