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
  virtual void Visit(const CtInput& node) = 0;
  virtual void Visit(const CtAdd& node) = 0;
  virtual void Visit(const CtMul& node) = 0;
  virtual void Visit(const CtPtAdd& node) = 0;
  virtual void Visit(const CtPtMul& node) = 0;
  virtual void Visit(const CtRotate& node) = 0;
};

}  // namespace janncy

#endif  // JANNCY_CT_GRAPH_VISITOR_H_
