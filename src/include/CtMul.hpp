#ifndef CTMUL_HPP_
#define CTMUL_HPP_

#include "CtOp.hpp"

#include <string>

class CtMul : public CtOp {
public:
    CtMul(CtOp* parent0, CtOp* parent1)
        : CtOp({parent0, parent1}) {};
    std::string type_str() const { return "CtMul"; }
};

#endif  // CTMUL_HPP_
