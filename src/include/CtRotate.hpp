#ifndef CTROTATE_HPP_
#define CTROTATE_HPP_

#include "CtOp.hpp"

#include <string>

class CtRotate : public CtOp {
public:
    CtRotate(CtOp* parent)
        : CtOp({parent}) {};
    std::string type_str() const { return "CtRotate"; }
};

#endif  // CTROTATE_HPP_
