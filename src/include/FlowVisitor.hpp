#ifndef FLOWVISITOR_HPP_
#define FLOWVISITOR_HPP_

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
    virtual void visit(Flow* flow, ConvLayer* node) = 0;
    virtual void visit(Flow* flow, FullyConnected* node) = 0;
    virtual void visit(Flow* flow, AveragePool* node) = 0;
    virtual void visit(Flow* flow, BatchNormalization* node) = 0;
    virtual void visit(Flow* flow, Add* node) = 0;
    virtual void visit(Flow* flow, Input* node) = 0;
    virtual void visit(Flow* flow, ReLU* node) = 0;
    virtual void visit(Flow* flow, MaxPool* node) = 0;
    virtual void visit(Flow* flow, Flatten* node) = 0;
};

#endif  // FLOWVISITOR_HPP_
