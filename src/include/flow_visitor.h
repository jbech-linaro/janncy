#ifndef JANNCY_FLOW_VISITOR_H_
#define JANNCY_FLOW_VISITOR_H_

namespace janncy {

class FlowNode;
class ConvLayer;
class FullyConnected;
class AveragePool;
class BatchNormalization;
class Add;
class Input;
class ReLU;
class MaxPool;
class Flatten;

class FlowVisitor {
 public:
  virtual void Visit(ConvLayer& node) = 0;
  virtual void Visit(FullyConnected& node) = 0;
  virtual void Visit(AveragePool& node) = 0;
  virtual void Visit(BatchNormalization& node) = 0;
  virtual void Visit(Add& node) = 0;
  virtual void Visit(Input& node) = 0;
  virtual void Visit(ReLU& node) = 0;
  virtual void Visit(MaxPool& node) = 0;
  virtual void Visit(Flatten& node) = 0;
};

}  // namespace janncy

#endif  // JANNCY_FLOW_VISITOR_H_
