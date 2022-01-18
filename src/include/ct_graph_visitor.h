#ifndef JANNCY_CT_GRAPH_VISITOR_H_
#define JANNCY_CT_GRAPH_VISITOR_H_

namespace janncy {

class CtOp;
class CtAdd;
class CtMul;
class CtPtAdd;
class CtPtMul;
class CtRotate;
class CtInput;

class CtGraphVisitor {
 public:
  virtual void Visit(CtInput& node) = 0;
  virtual void Visit(CtAdd& node) = 0;
  virtual void Visit(CtMul& node) = 0;
  virtual void Visit(CtPtAdd& node) = 0;
  virtual void Visit(CtPtMul& node) = 0;
  virtual void Visit(CtRotate& node) = 0;
};

}  // namespace janncy

#endif  // JANNCY_CT_GRAPH_VISITOR_H_
