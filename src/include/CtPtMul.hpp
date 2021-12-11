#ifndef CTPTMUL_HPP_
#define CTPTMUL_HPP_

#include "CtOp.hpp"

#include <string>
#include <vector>

class CtGraphVisitor;

class CtPtMul : public CtOp {
  public:
    static CtPtMul* create(CtOp* parent) { return new CtPtMul(parent); }
    std::string type_str() const override { return "CtPtMul"; }
    std::vector<double> value() const { return value_; }
    void visit(CtGraphVisitor* visitor) override;

  private:
    // TODO(nsamar): Add support for passing in value, instead of initializing
    // to 1s
    CtPtMul(CtOp* parent) : CtOp({parent}), value_(32, 1.0){};
    std::vector<double> value_;
};

#endif  // CTPTMUL_HPP_
