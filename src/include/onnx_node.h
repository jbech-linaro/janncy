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
  OnnxNode(OnnxNodeId name, std::vector<OnnxNodeId> inputs,
           OnnxNodeId output_name)
      : name_(name), inputs_(inputs), output_(output_name) {}
  OnnxNode(OnnxNode&&) = default;
  OnnxNode(const OnnxNode&) = delete;
  OnnxNode& operator=(const OnnxNode&) = delete;
  virtual ~OnnxNode() {}

  OnnxNodeId name() const { return name_; }
  std::vector<OnnxNodeId> inputs() const { return inputs_; }
  OnnxNodeId output() const { return output_; }

 private:
  OnnxNodeId name_;
  std::vector<OnnxNodeId> inputs_;
  OnnxNodeId output_;
};

class OnnxConvLayer : public OnnxNode {
 public:
  OnnxConvLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId W,
                OnnxNodeId output_name)
      : OnnxNode(name, {X, W}, output_name) {}
};

class OnnxAveragePoolLayer : public OnnxNode {
 public:
  OnnxAveragePoolLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId output_name,
                       KernelAttributes kernel_attributes)
      : OnnxNode(name, {X}, output_name),
        kernel_attributes_(kernel_attributes) {}

 private:
  KernelAttributes kernel_attributes_;
};

class OnnxReluLayer : public OnnxNode {
 public:
  OnnxReluLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId output_name)
      : OnnxNode(name, {X}, output_name) {}
};

class OnnxMaxPoolLayer : public OnnxNode {
 public:
  OnnxMaxPoolLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId output_name,
                   KernelAttributes kernel_attributes)
      : OnnxNode(name, {X}, output_name),
        kernel_attributes_(kernel_attributes) {}

 private:
  KernelAttributes kernel_attributes_;
};

class OnnxFullyConnectedLayer : public OnnxNode {
 public:
  OnnxFullyConnectedLayer(OnnxNodeId name, OnnxNodeId A, OnnxNodeId B,
                          OnnxNodeId output_name)
      : OnnxNode(name, {A, B}, output_name) {}
};

class OnnxAddLayer : public OnnxNode {
 public:
  OnnxAddLayer(OnnxNodeId name, OnnxNodeId A, OnnxNodeId B,
               OnnxNodeId output_name)
      : OnnxNode(name, {A, B}, output_name) {}
};

class OnnxGlobalAveragePoolLayer : public OnnxNode {
 public:
  OnnxGlobalAveragePoolLayer(OnnxNodeId name, OnnxNodeId X,
                             OnnxNodeId output_name)
      : OnnxNode(name, {X}, output_name) {}
};

class OnnxFlattenLayer : public OnnxNode {
 public:
  OnnxFlattenLayer(OnnxNodeId name, OnnxNodeId X, OnnxNodeId output_name,
                   int axis)
      : OnnxNode(name, {X}, output_name), axis_(axis) {
    PANIC_IF(axis != 1);
  }
  int axis() const { return axis_; }

 private:
  int axis_;
};

class OnnxInitializer : public OnnxNode {
 public:
  OnnxInitializer(OnnxNodeId name, Shape shape)
      : OnnxNode(name, {}, name), shape_(shape) {}

 private:
  Shape shape_;
};

class OnnxInput : public OnnxNode {
 public:
  OnnxInput(OnnxNodeId name, Shape shape)
      : OnnxNode(name, {}, name), shape_(shape) {}

 private:
  Shape shape_;
};

using OwnedOnnxNodeVec = std::vector<std::unique_ptr<OnnxNode>>;

}  // namespace janncy

#endif  // JANNCY_ONNX_NODE_H_
