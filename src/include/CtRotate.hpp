#ifndef CTROTATE_HPP_
#define CTROTATE_HPP_

#include "CtOp.hpp"

#include <string>

class CtRotate : public CtOp {
  public:
    static CtRotate* create(CtOp* parent) { return new CtRotate(parent); }
    std::string type_str() const { return "CtRotate"; }

  private:
    CtRotate(CtOp* parent) : CtOp({parent}){};
};

#endif  // CTROTATE_HPP_
