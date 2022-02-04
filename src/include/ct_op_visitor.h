#ifndef JANNCY_CT_OP_VISITOR_H_
#define JANNCY_CT_OP_VISITOR_H_

namespace janncy {

class CtOp;
class AddCC;
class AddCP;
class AddCS;
class MulCC;
class MulCP;
class MulCS;
class RotateC;
class CtInput;

class CtOpVisitor {
 public:
  CtOpVisitor() = default;
  virtual ~CtOpVisitor() {}
  CtOpVisitor(const CtOpVisitor&) = delete;
  CtOpVisitor(CtOpVisitor&&) = default;
  CtOpVisitor& operator=(const CtOpVisitor&) = delete;

  virtual void Visit(const CtInput& node) = 0;
  virtual void Visit(const AddCC& node) = 0;
  virtual void Visit(const AddCP& node) = 0;
  virtual void Visit(const AddCS& node) = 0;
  virtual void Visit(const MulCC& node) = 0;
  virtual void Visit(const MulCP& node) = 0;
  virtual void Visit(const MulCS& node) = 0;
  virtual void Visit(const RotateC& node) = 0;
};

}  // namespace janncy

#endif  // JANNCY_CT_OP_VISITOR_H_
