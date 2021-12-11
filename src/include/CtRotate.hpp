#ifndef CTROTATE_HPP_
#define CTROTATE_HPP_

#include "CtOp.hpp"

#include <string>

class CtGraphVisitor;

class CtRotate : public CtOp {
  public:
    static CtRotate* create(CtOp* parent) { return new CtRotate(parent); }
    std::string type_str() const override { return "CtRotate"; }
    int amt() const { return amt_; }
    void visit(CtGraphVisitor* visitor) override;

  private:
    // TODO(nsamar): Add support for passing in amt, instead of initializing
    // to 1
    CtRotate(CtOp* parent) : CtOp({parent}), amt_(1){};
    int amt_;
};

#endif  // CTROTATE_HPP_
