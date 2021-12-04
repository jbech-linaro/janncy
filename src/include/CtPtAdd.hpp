#ifndef CTPTADD_HPP_
#define CTPTADD_HPP_

#include "CtOp.hpp"

#include <string>

class CtPtAdd : public CtOp {
public:
    CtPtAdd(CtOp* parent)
        : CtOp({parent}) {};
    std::string type_str() const { return "CtPtAdd"; }
};

#endif  // CTPTADD_HPP_
