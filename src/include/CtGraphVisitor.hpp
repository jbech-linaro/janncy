#ifndef CTGRAPHVISITOR_HPP_
#define CTGRAPHVISITOR_HPP_

namespace janncy {

class CtGraph;

class CtOp;
class CtAdd;
class CtMul;
class CtPtAdd;
class CtPtMul;
class CtRotate;
class CtInput;

class CtGraphVisitor {
  public:
    virtual void visit(CtGraph* ct_graph, CtInput* node) = 0;
    virtual void visit(CtGraph* ct_graph, CtAdd* node) = 0;
    virtual void visit(CtGraph* ct_graph, CtMul* node) = 0;
    virtual void visit(CtGraph* ct_graph, CtPtAdd* node) = 0;
    virtual void visit(CtGraph* ct_graph, CtPtMul* node) = 0;
    virtual void visit(CtGraph* ct_graph, CtRotate* node) = 0;
};

}  // namespace janncy

#endif  // CTGRAPHVISITOR_HPP_
