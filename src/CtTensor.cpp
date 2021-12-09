#include "include/CtTensor.hpp"

#include <vector>

class CtOp;

CtTensor::CtTensor(std::vector<CtOp*> parents) : parents_(parents) {}

std::vector<CtOp*> CtTensor::get_ct_ops() const { return parents_; }
