#ifndef CTPTADD_HPP_
#define CTPTADD_HPP_

#include "CtOp.hpp"

#include <string>

class CtPtAdd : public CtOp {
  public:
    static CtPtAdd* create(CtOp* parent) { return new CtPtAdd(parent); }
    std::string type_str() const { return "CtPtAdd"; }

  private:
    CtPtAdd(CtOp* parent) : CtOp({parent}){};
};

#endif  // CTPTADD_HPP_
