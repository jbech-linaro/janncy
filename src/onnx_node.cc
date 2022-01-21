#include "include/onnx_node.h"

#include <string>

#include <onnx/defs/tensor_proto_util.h>
#include <onnx/onnx_pb.h>
#include <onnx/proto_utils.h>

#include "include/kernel_attributes.h"
#include "include/panic.h"
#include "include/shape.h"

namespace janncy {

namespace {

const std::string ATTR_STRIDES = "strides";
const std::string ATTR_PADDING = "pads";
const std::string ATTR_AUTO_PAD = "auto_pad";
const std::string ATTR_KERNEL_SHAPE = "kernel_shape";
const std::string ATTR_AXIS = "axis";

}  // namespace

OnnxNode::OnnxNode(const onnx::NodeProto* node_proto,
                   std::vector<Shape> input_shapes)
    : node_proto_(node_proto), input_shapes_(std::move(input_shapes)) {}

OnnxNode::OnnxNode(Shape shape)
    : node_proto_(nullptr), input_shapes_({}), shape_(std::move(shape)) {}

std::vector<Shape> OnnxNode::input_shapes() const { return input_shapes_; }

std::vector<std::string> OnnxNode::output() const {
  std::vector<std::string> result;
  for (auto out_val : node_proto_->output()) {
    result.push_back(out_val);
  }
  return result;
}

const onnx::AttributeProto* OnnxNode::attribute(
    const std::string& attr_name) const {
  for (const auto& attr : node_proto_->attribute()) {
    if (attr.name() == attr_name) {
      return &attr;
    }
  }
  return nullptr;
}

Shape OnnxNode::shape() const { return shape_; }

const onnx::AttributeProto* OnnxNode::typed_attribute(
    const std::string& attr_name,
    const onnx::AttributeProto::AttributeType& attr_type) const {
  auto attr = attribute(attr_name);
  if ((attr == nullptr) || (attr->type() != attr_type)) {
    return nullptr;
  } else {
    return attr;
  }
}

bool OnnxNode::AttributeExists(const std::string& attr_name) const {
  return attribute(attr_name) != nullptr;
}

int OnnxNode::int_attribute(const std::string& attr_name) const {
  auto attr = typed_attribute(attr_name, onnx::AttributeProto::INT);
  PANIC_IF(attr == nullptr, "INT attribute `" + attr_name + "' not found!");
  return attr->i();
}

std::vector<std::string> OnnxNode::input() const {
  std::vector<std::string> result;
  for (auto in_val : node_proto_->input()) {
    result.push_back(in_val);
  }
  return result;
}

std::vector<int> OnnxNode::ints_attribute(const std::string& attr_name) const {
  auto attr = typed_attribute(attr_name, onnx::AttributeProto::INTS);
  PANIC_IF(attr == nullptr, "INTS attribute `" + attr_name + "' not found!");
  return std::vector<int>(attr->ints().begin(), attr->ints().end());
}

std::vector<int> OnnxNode::optional_ints_attribute(
    const std::string& attr_name) const {
  auto attr = typed_attribute(attr_name, onnx::AttributeProto::INTS);
  if (attr == nullptr) {
    return {};
  } else {
    return std::vector<int>(attr->ints().begin(), attr->ints().end());
  }
}

std::vector<int> OnnxNode::strides() const {
  return optional_ints_attribute(ATTR_STRIDES);
}
std::vector<int> OnnxNode::padding() const {
  return optional_ints_attribute(ATTR_PADDING);
}
Shape OnnxNode::kernel_shape() const {
  return Shape(optional_ints_attribute(ATTR_KERNEL_SHAPE));
}
KernelAttributes OnnxNode::kernel_for_pooling() const {
  return KernelAttributes(kernel_shape(), strides(), padding());
}

std::string OnnxNode::op_type() const { return node_proto_->op_type(); }

std::string OnnxNode::name() const { return node_proto_->name(); }

}  // namespace janncy
