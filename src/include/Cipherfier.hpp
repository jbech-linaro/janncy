#ifndef CIPHERFIER_HPP_
#define CIPHERFIER_HPP_

#include "CtTensor.hpp"
#include "FlowVisitor.hpp"
#include "Panic.hpp"

#include <unordered_map>

class FlowNode;
class Flow;

class ConvLayer;
class FullyConnected;
class AveragePool;
class BatchNormalization;
class Add;
class Input;
class ReLU;
class Flatten;

class CtGraph;

class Cipherfier : public FlowVisitor {
  public:
    Cipherfier();

    void visit(Flow* flow, ConvLayer* node) override;
    void visit(Flow* flow, FullyConnected* node) override;
    void visit(Flow* flow, AveragePool* node) override;
    void visit(Flow* flow, BatchNormalization* node) override;
    void visit(Flow* flow, Add* node) override;
    void visit(Flow* flow, Input* node) override;
    void visit(Flow* flow, ReLU* node) override;
    void visit(Flow* flow, MaxPool* node) override;
    void visit(Flow* flow, Flatten* node) override;

    CtGraph* ct_graph() const { return ct_graph_; }

  private:
    void register_node(const FlowNode* node, const std::vector<CtOp*>& ct_ops);
    CtTensor ct_op(const FlowNode* node);
    std::vector<CtTensor> parents(Flow* flow, FlowNode* node);
    std::unordered_map<const FlowNode*, CtTensor> ct_map_;
    CtGraph* ct_graph_;
};

#endif  // CIPHERFIER_HPP_
