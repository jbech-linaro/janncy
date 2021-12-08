#ifndef CTPTMUL_HPP_
#define CTPTMUL_HPP_

#include "CtOp.hpp"

#include <string>

class CtPtMul : public CtOp {
  public:
    static CtPtMul* create(CtOp* parent) { return new CtPtMul(parent); }
    std::string type_str() const { return "CtPtMul"; }

  private:
    CtPtMul(CtOp* parent) : CtOp({parent}){};
};

#endif  // CTPTMUL_HPP_
