#ifndef JANNCY_ONNX_NODE_H_
#define JANNCY_ONNX_NODE_H_

#include <string>
#include <vector>

#include "include/kernel_attributes.h"
#include "include/panic.h"
#include "include/shape.h"

namespace janncy {

using OnnxNodeId = std::string;

class OnnxNode {
 public:
  OnnxNode(OnnxNodeId name, std::vector<OnnxNodeId> inputs)
      : name_(name), inputs_(inputs) {}
  OnnxNode(OnnxNode&&) = default;
  OnnxNode(const OnnxNode&) = delete;
  OnnxNode& operator=(const OnnxNode&) = delete;
  virtual ~OnnxNode() {}

  OnnxNodeId name() const { return name_; }
  std::vector<OnnxNodeId> inputs() const { return inputs_; }

 private:
  OnnxNodeId name_;
  std::vector<OnnxNodeId> inputs_;
};

class OnnxConvLayer : public OnnxNode {
 public:
  OnnxConvLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId W)
      : OnnxNode(name, {X, W}) {}
};

class OnnxAveragePoolLayer : public OnnxNode {
 public:
  OnnxAveragePoolLayer(OnnxNodeId name, OnnxNodeId X,
                       KernelAttributes kernel_attributes)
      : OnnxNode(name, {X}), kernel_attributes_(kernel_attributes) {}

 private:
  KernelAttributes kernel_attributes_;
};

class OnnxReluLayer : public OnnxNode {
 public:
  OnnxReluLayer(OnnxNodeId name, OnnxNodeId X) : OnnxNode(name, {X}) {}
};

class OnnxMaxPoolLayer : public OnnxNode {
 public:
  OnnxMaxPoolLayer(OnnxNodeId name, OnnxNodeId X,
                   KernelAttributes kernel_attributes)
      : OnnxNode(name, {X}), kernel_attributes_(kernel_attributes) {}

 private:
  KernelAttributes kernel_attributes_;
};

class OnnxFullyConnectedLayer : public OnnxNode {
 public:
  OnnxFullyConnectedLayer(OnnxNodeId name, OnnxNodeId A, OnnxNodeId B)
      : OnnxNode(name, {A, B}) {}
};

class OnnxAddLayer : public OnnxNode {
 public:
  OnnxAddLayer(OnnxNodeId name, OnnxNodeId A, OnnxNodeId B)
      : OnnxNode(name, {A, B}) {}
};

class OnnxGlobalAveragePoolLayer : public OnnxNode {
 public:
  OnnxGlobalAveragePoolLayer(OnnxNodeId name, OnnxNodeId X,
                             KernelAttributes kernel_attributes)
      : OnnxNode(name, {X}) {}
};

class OnnxFlattenLayer : public OnnxNode {
 public:
  OnnxFlattenLayer(OnnxNodeId name, OnnxNodeId X, int axis)
      : OnnxNode(name, {X}), axis_(axis) {
    PANIC_IF(axis != 1);
  }
  int axis() const { return axis_; }

 private:
  int axis_;
};

class OnnxInitializer : public OnnxNode {
 public:
  OnnxInitializer(OnnxNodeId name, Shape shape)
      : OnnxNode(name, {}), shape_(shape) {}

 private:
  Shape shape_;
};

class OnnxInput : public OnnxNode {
 public:
  OnnxInput(OnnxNodeId name, Shape shape) : OnnxNode(name, {}), shape_(shape) {}

 private:
  Shape shape_;
};

}  // namespace janncy

#endif  // JANNCY_ONNX_NODE_H_
