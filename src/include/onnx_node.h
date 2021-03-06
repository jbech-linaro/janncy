#ifndef JANNCY_ONNX_NODE_H_
#define JANNCY_ONNX_NODE_H_

#include <string>
#include <vector>

#include <onnx/defs/tensor_proto_util.h>
#include <onnx/onnx_pb.h>
#include <onnx/proto_utils.h>

#include "kernel_attributes.h"
#include "shape.h"

namespace janncy {

// TODO(nsamar): OnnxNode should not keep a NodeProto pointer,
// There should just be a convenience function outside of OnnxNode
// that initializes all relevant attributes by reading node_proto
// fields and call a do-nothing OnnxNode constructor that assigns
// these values to the attributes in OnnxNode.
class OnnxNode {
 public:
  OnnxNode(const onnx::NodeProto& node_proto, std::vector<Shape> input_shapes);
  explicit OnnxNode(Shape shape);

  std::vector<std::string> input() const;
  std::string op_type() const;
  std::vector<Shape> input_shapes() const;
  KernelAttributes kernel() const;
  int output_channel_count() const;
  std::vector<std::string> output() const;
  std::string name() const;

  int axis() const;

 private:
  const onnx::AttributeProto* attribute(const std::string& attr_name) const;
  const onnx::AttributeProto* typed_attribute(
      const std::string& attr_name,
      const onnx::AttributeProto::AttributeType& attr_type) const;
  Shape kernel_shape() const;
  int int_attribute(const std::string& attr_name) const;
  std::vector<int> strides() const;
  std::vector<int> padding() const;
  bool AttributeExists(const std::string& attr_name) const;
  std::vector<int> ints_attribute(const std::string& attr_name) const;
  std::vector<int> optional_ints_attribute(const std::string& attr_name) const;
  const onnx::NodeProto* node_proto_;
  std::vector<Shape> input_shapes_;
  Shape shape_;
};

}  // namespace janncy

#endif  // JANNCY_ONNX_NODE_H_
