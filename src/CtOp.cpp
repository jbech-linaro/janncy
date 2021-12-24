#include "include/CtOp.hpp"

#include <sstream>
#include <string>

CtOp::CtOp(std::string type_str) : type_str_(type_str) {}

std::string CtOp::str() const {
    std::stringstream result;
    result << "[" << this << "] ";
    result << type_str_;
    return result.str();
}
