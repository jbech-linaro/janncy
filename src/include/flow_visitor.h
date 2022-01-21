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
  virtual void Visit(const ConvLayer& node) = 0;
  virtual void Visit(const FullyConnected& node) = 0;
  virtual void Visit(const AveragePool& node) = 0;
  virtual void Visit(const BatchNormalization& node) = 0;
  virtual void Visit(const Add& node) = 0;
  virtual void Visit(const Input& node) = 0;
  virtual void Visit(const ReLU& node) = 0;
  virtual void Visit(const MaxPool& node) = 0;
  virtual void Visit(const Flatten& node) = 0;
};

}  // namespace janncy

#endif  // JANNCY_FLOW_VISITOR_H_
