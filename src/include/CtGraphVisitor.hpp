#ifndef CTGRAPHVISITOR_HPP_
#define CTGRAPHVISITOR_HPP_

class CtOp;
class CtAdd;
class CtMul;
class CtPtAdd;
class CtPtMul;
class CtRotate;
class CtInput;

class CtGraphVisitor {
  public:
    virtual void visit(CtInput* node) = 0;
    virtual void visit(CtAdd* node) = 0;
    virtual void visit(CtMul* node) = 0;
    virtual void visit(CtPtAdd* node) = 0;
    virtual void visit(CtPtMul* node) = 0;
    virtual void visit(CtRotate* node) = 0;
};

#endif  // CTGRAPHVISITOR_HPP_
