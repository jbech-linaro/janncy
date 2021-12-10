#ifndef FLOWNODE_HPP_
#define FLOWNODE_HPP_

#include "CtTensor.hpp"
#include "Node.hpp"
#include "Panic.hpp"
#include "Tensor.hpp"

#include <iostream>
#include <string>
#include <vector>

class FlowVisitor;
class Flow;
template <class T> class Graph;

class FlowNode : public Node<FlowNode> {
  public:
    FlowNode(Graph<FlowNode>* graph, Tensor output_tensor);
    FlowNode(std::vector<FlowNode*> parents, Tensor output_tensor);

    Tensor output_tensor() const;
    Tensor input_tensor() const;
    std::vector<int> shape() const { return output_tensor().shape(); }

    FlowNode(const FlowNode&) = delete;
    FlowNode& operator=(const FlowNode&) = delete;
    FlowNode(FlowNode&&) = delete;
    FlowNode& operator=(FlowNode&&) = delete;

    virtual void visit(FlowVisitor* visitor) = 0;

    void set_name(std::string name);

    std::string str() const;
    virtual std::string type_str() const = 0;

  protected:
    Tensor output_tensor_;
    std::string name_;
    ~FlowNode() {
        panic(
            "FlowNodes must not be created as automatic (stack) variable. This "
            "was probably caused by constructing an automatic variable of a "
            "FlowNode's deribed type (e.g. ConvLayer, FullyConnected, etc.). "
            "Please make sure all classes derived from FlowNode have private "
            "constructors with a static `create()' method. This will make code "
            "that creates automatic FlowNodes not compile (which is desired).");
    }  // Prohibit FlowNode objects on stack
};

#endif  // FLOWNODE_HPP_
