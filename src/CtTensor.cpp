#include "include/CtTensor.hpp"
#include "include/CtOp.hpp"

#include <vector>

namespace janncy {

CtTensor::CtTensor(std::vector<CtOp*> parents) : parents_(parents) {}

std::vector<CtOp*> CtTensor::get_ct_ops() const { return parents_; }

}  // namespace janncy
