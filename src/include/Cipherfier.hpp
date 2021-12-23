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

    void visit(ConvLayer* node) override;
    void visit(FullyConnected* node) override;
    void visit(AveragePool* node) override;
    void visit(BatchNormalization* node) override;
    void visit(Add* node) override;
    void visit(Input* node) override;
    void visit(ReLU* node) override;
    void visit(MaxPool* node) override;
    void visit(Flatten* node) override;

    CtGraph* ct_graph() const { return ct_graph_; }

  private:
    void register_node(const FlowNode* node, const std::vector<CtOp*>& ct_ops);
    CtTensor ct_op(const FlowNode* node);
    std::vector<CtTensor> parents(const FlowNode* node);
    std::unordered_map<const FlowNode*, CtTensor> ct_map_;
    CtGraph* ct_graph_;
};

#endif  // CIPHERFIER_HPP_
