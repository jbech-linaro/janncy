#ifndef CTADD_HPP_
#define CTADD_HPP_

#include "CtOp.hpp"

#include <string>

class CtAdd : public CtOp {
public:
    CtAdd(CtOp* parent0, CtOp* parent1)
        : CtOp({parent0, parent1}) {};
    std::string type_str() const { return "CtAdd"; }
};

#endif  // CTADD_HPP_
