#include "include/CtOp.hpp"

#include <sstream>
#include <string>

std::string CtOp::str() const {
    std::stringstream result;
    result << "[" << this << "] ";
    result << type_str();
    return result.str();
}
