#ifndef JANNCY_ONNX_NODE_VISITOR_H_
#define JANNCY_ONNX_NODE_VISITOR_H_

namespace janncy {

class OnnxNode;
class OnnxConvLayer;
class OnnxFullyConnectedLayer;
class OnnxAveragePoolLayer;
class OnnxBatchNormalizationLayer;
class OnnxAddLayer;
class OnnxInput;
class OnnxReluLayer;
class OnnxMaxPoolLayer;
class OnnxFlattenLayer;
class OnnxGlobalAveragePoolLayer;

class OnnxNodeVisitor {
 public:
  OnnxNodeVisitor() = default;
  OnnxNodeVisitor(OnnxNodeVisitor&&) = default;
  virtual ~OnnxNodeVisitor() {}
  OnnxNodeVisitor(const OnnxNodeVisitor&) = delete;
  OnnxNodeVisitor& operator=(const OnnxNodeVisitor&) = delete;

  virtual void Visit(const OnnxNode& onnx_node) = 0;
  virtual void Visit(const OnnxConvLayer& onnx_node) = 0;
  virtual void Visit(const OnnxFullyConnectedLayer& onnx_node) = 0;
  virtual void Visit(const OnnxAveragePoolLayer& onnx_node) = 0;
  virtual void Visit(const OnnxGlobalAveragePoolLayer& onnx_node) = 0;
  virtual void Visit(const OnnxBatchNormalizationLayer& onnx_node) = 0;
  virtual void Visit(const OnnxAddLayer& onnx_node) = 0;
  virtual void Visit(const OnnxInput& onnx_node) = 0;
  virtual void Visit(const OnnxReluLayer& onnx_node) = 0;
  virtual void Visit(const OnnxMaxPoolLayer& onnx_node) = 0;
  virtual void Visit(const OnnxFlattenLayer& onnx_node) = 0;
};

}  // namespace janncy

#endif  // JANNCY_ONNX_NODE_VISITOR_H_
