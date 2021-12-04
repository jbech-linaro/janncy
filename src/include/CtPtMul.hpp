#ifndef CTPTMUL_HPP_
#define CTPTMUL_HPP_

#include "CtOp.hpp"

#include <string>

class CtPtMul : public CtOp {
public:
    CtPtMul(CtOp* parent)
        : CtOp({parent}) {};
    std::string type_str() const { return "CtPtMul"; }
};

#endif  // CTPTMUL_HPP_
