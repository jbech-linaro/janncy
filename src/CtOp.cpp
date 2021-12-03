#include "include/CtOp.hpp"

#include <string>
#include <sstream>

std::string CtOp::str() const {
    std::stringstream result;
    result << "[" << this << "] ";
    result << type_str();
    return result.str();
}
