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

    void register_node(FlowNode* node, std::vector<CtOp*> ct_ops);

    CtGraph* ct_graph() const { return ct_graph_; }

  private:
    CtTensor ct_op(FlowNode* node);
    std::vector<CtTensor> parents(FlowNode* node);
    std::vector<CtTensor> get_parents(FlowNode* node);
    std::unordered_map<FlowNode*, CtTensor> ct_map_;
    CtGraph* ct_graph_;
};

#endif  // CIPHERFIER_HPP_
