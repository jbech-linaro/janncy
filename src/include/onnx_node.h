#ifndef JANNCY_ONNX_NODE_H_
#define JANNCY_ONNX_NODE_H_

#include <string>
#include <vector>

#include "include/kernel_attributes.h"
#include "include/onnx_node_visitor.h"
#include "include/panic.h"
#include "include/shape.h"

namespace janncy {

using OnnxNodeId = std::string;

class OnnxNode {
 public:
  OnnxNode(OnnxNodeId name, OnnxNodeId output_name)
      : name_(name), output_(output_name) {}
  OnnxNode(OnnxNode&&) = default;
  OnnxNode(const OnnxNode&) = delete;
  OnnxNode& operator=(const OnnxNode&) = delete;
  virtual ~OnnxNode() {}

  OnnxNodeId name() const { return name_; }
  virtual std::vector<OnnxNodeId> inputs() const = 0;
  OnnxNodeId output() const { return output_; }

  virtual void Accept(OnnxNodeVisitor& visitor) const = 0;

 private:
  OnnxNodeId name_;
  OnnxNodeId output_;
};

class OnnxConvLayer : public OnnxNode {
 public:
  OnnxConvLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId W,
                OnnxNodeId output_name, std::vector<int> strides,
                std::vector<int> padding)
      : OnnxNode(name, output_name),
        X_(X),
        W_(W),
        strides_(strides),
        padding_(padding) {}

  OnnxNodeId W() const { return W_; }
  OnnxNodeId X() const { return X_; }
  void Accept(OnnxNodeVisitor& visitor) const override { visitor.Visit(*this); }
  std::vector<OnnxNodeId> inputs() const override { return {X_, W_}; }
  std::vector<int> strides() const { return strides_; }
  std::vector<int> padding() const { return padding_; }

 private:
  OnnxNodeId X_;
  OnnxNodeId W_;
  std::vector<int> strides_;
  std::vector<int> padding_;
};

class OnnxAveragePoolLayer : public OnnxNode {
 public:
  OnnxAveragePoolLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId output_name,
                       KernelAttributes kernel_attributes)
      : OnnxNode(name, output_name),
        X_(X),
        kernel_attributes_(kernel_attributes) {}

  OnnxNodeId X() const { return X_; }
  void Accept(OnnxNodeVisitor& visitor) const override { visitor.Visit(*this); }
  std::vector<OnnxNodeId> inputs() const override { return {X_}; }
  KernelAttributes kernel_attributes() const { return kernel_attributes_; }

 private:
  OnnxNodeId X_;
  KernelAttributes kernel_attributes_;
};

class OnnxReluLayer : public OnnxNode {
 public:
  OnnxReluLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId output_name)
      : OnnxNode(name, output_name), X_(X) {}

  OnnxNodeId X() const { return X_; }
  void Accept(OnnxNodeVisitor& visitor) const override { visitor.Visit(*this); }
  std::vector<OnnxNodeId> inputs() const override { return {X_}; }

 private:
  OnnxNodeId X_;
};

class OnnxMaxPoolLayer : public OnnxNode {
 public:
  OnnxMaxPoolLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId output_name,
                   KernelAttributes kernel_attributes)
      : OnnxNode(name, output_name),
        X_(X),
        kernel_attributes_(kernel_attributes) {}

  OnnxNodeId X() const { return X_; }
  void Accept(OnnxNodeVisitor& visitor) const override { visitor.Visit(*this); }
  std::vector<OnnxNodeId> inputs() const override { return {X_}; }
  KernelAttributes kernel_attributes() const { return kernel_attributes_; }

 private:
  OnnxNodeId X_;
  KernelAttributes kernel_attributes_;
};

class OnnxFullyConnectedLayer : public OnnxNode {
 public:
  OnnxFullyConnectedLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId W,
                          OnnxNodeId output_name)
      : OnnxNode(name, output_name), X_(X), W_(W) {}

  OnnxNodeId X() const { return X_; }
  OnnxNodeId W() const { return W_; }
  void Accept(OnnxNodeVisitor& visitor) const override { visitor.Visit(*this); }
  std::vector<OnnxNodeId> inputs() const override { return {X_, W_}; }

 private:
  OnnxNodeId X_;
  OnnxNodeId W_;
};

class OnnxAddLayer : public OnnxNode {
 public:
  OnnxAddLayer(OnnxNodeId name, OnnxNodeId A, OnnxNodeId B,
               OnnxNodeId output_name)
      : OnnxNode(name, output_name), A_(A), B_(B) {}

  OnnxNodeId A() const { return A_; }
  OnnxNodeId B() const { return B_; }
  void Accept(OnnxNodeVisitor& visitor) const override { visitor.Visit(*this); }
  std::vector<OnnxNodeId> inputs() const override { return {A_, B_}; }

 private:
  OnnxNodeId A_;
  OnnxNodeId B_;
};

class OnnxGlobalAveragePoolLayer : public OnnxNode {
 public:
  OnnxGlobalAveragePoolLayer(OnnxNodeId name, OnnxNodeId X,
                             OnnxNodeId output_name)
      : OnnxNode(name, output_name), X_(X) {}

  OnnxNodeId X() const { return X_; }
  void Accept(OnnxNodeVisitor& visitor) const override { visitor.Visit(*this); }
  std::vector<OnnxNodeId> inputs() const override { return {X_}; }

 private:
  OnnxNodeId X_;
};

class OnnxBatchNormalizationLayer : public OnnxNode {
 public:
  OnnxBatchNormalizationLayer(OnnxNodeId name, OnnxNodeId X,
                              OnnxNodeId output_name)
      : OnnxNode(name, output_name), X_(X) {}

  OnnxNodeId X() const { return X_; }
  void Accept(OnnxNodeVisitor& visitor) const override { visitor.Visit(*this); }
  std::vector<OnnxNodeId> inputs() const override { return {X_}; }

 private:
  OnnxNodeId X_;
};

class OnnxFlattenLayer : public OnnxNode {
 public:
  OnnxFlattenLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId output_name,
                   int axis)
      : OnnxNode(name, output_name), X_(X), axis_(axis) {
    PANIC_IF(axis != 1);
  }

  OnnxNodeId X() const { return X_; }
  void Accept(OnnxNodeVisitor& visitor) const override { visitor.Visit(*this); }
  int axis() const { return axis_; }
  std::vector<OnnxNodeId> inputs() const override { return {X_}; }

 private:
  OnnxNodeId X_;
  int axis_;
};

class OnnxInitializer : public OnnxNode {
 public:
  OnnxInitializer(OnnxNodeId name, Shape shape)
      : OnnxNode(name, name), shape_(shape) {}

  void Accept(OnnxNodeVisitor& visitor) const override { visitor.Visit(*this); }
  std::vector<OnnxNodeId> inputs() const override { return {}; }
  Shape shape() const { return shape_; }

 private:
  Shape shape_;
};

class OnnxInput : public OnnxNode {
 public:
  OnnxInput(OnnxNodeId name, Shape shape)
      : OnnxNode(name, name), shape_(shape) {}

  void Accept(OnnxNodeVisitor& visitor) const override { visitor.Visit(*this); }
  std::vector<OnnxNodeId> inputs() const override { return {}; }
  Shape shape() const { return shape_; }

 private:
  Shape shape_;
};

using OwnedOnnxNodeVec = std::vector<std::unique_ptr<OnnxNode>>;

}  // namespace janncy

#endif  // JANNCY_ONNX_NODE_H_
