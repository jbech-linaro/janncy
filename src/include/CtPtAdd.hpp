#ifndef CTPTADD_HPP_
#define CTPTADD_HPP_

#include "CtOp.hpp"

#include <string>
#include <vector>

class CtGraphVisitor;

class CtPtAdd : public CtOp {
  public:
    static CtPtAdd* create(CtOp* parent) { return new CtPtAdd(parent); }
    std::string type_str() const override { return "CtPtAdd"; }
    std::vector<double> value() const { return value_; }
    void visit(CtGraphVisitor* visitor) override;

  private:
    // TODO(nsamar): Add support for passing in value, instead of initializing
    // to 1s
    CtPtAdd(CtOp* parent)
        : CtOp({parent}), value_(std::vector<double>(32, 1)){};
    std::vector<double> value_;
};

#endif  // CTPTADD_HPP_
