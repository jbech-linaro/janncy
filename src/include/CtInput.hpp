#ifndef CTINPUT_HPP_
#define CTINPUT_HPP_

#include "CtOp.hpp"

#include <vector>
#include <string>

class CtInput : public CtOp {
public:
    CtInput() : CtOp({}) {};
    std::string type_str() const { return "CtInput"; }
};

#endif  // CTINPUT_HPP_
