#ifndef FLOWVISITOR_HPP_
#define FLOWVISITOR_HPP_

namespace janncy {

class Flow;

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
    virtual void visit(ConvLayer& node) = 0;
    virtual void visit(FullyConnected& node) = 0;
    virtual void visit(AveragePool& node) = 0;
    virtual void visit(BatchNormalization& node) = 0;
    virtual void visit(Add& node) = 0;
    virtual void visit(Input& node) = 0;
    virtual void visit(ReLU& node) = 0;
    virtual void visit(MaxPool& node) = 0;
    virtual void visit(Flatten& node) = 0;
};

}  // namespace janncy

#endif  // FLOWVISITOR_HPP_
