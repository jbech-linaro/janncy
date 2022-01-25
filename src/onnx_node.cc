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

OnnxNode::OnnxNode(const onnx::NodeProto& node_proto,
                   std::vector<Shape> input_shapes)
    : node_proto_(&node_proto), input_shapes_(std::move(input_shapes)) {}

// TODO(nsamar): This constructor should not exist, it is just a hack
// to be able to put onnx inputs into OnnxNode objects (hack needed
// because onnx inputs are not onnx::NodeProto's). When the need for the
// hack is removed, remove this constructor as well and make node_proto_
// a const reference instead of a pointer.
OnnxNode::OnnxNode(Shape shape)
    : node_proto_(nullptr), input_shapes_({}), shape_(std::move(shape)) {}

std::vector<Shape> OnnxNode::input_shapes() const { return input_shapes_; }

int OnnxNode::axis() const {
  PANIC_IF(op_type() != "Flatten");
  if (!AttributeExists(ATTR_AXIS)) {
    return 1;
  }
  return int_attribute(ATTR_AXIS);
}

std::vector<std::string> OnnxNode::output() const {
  std::vector<std::string> result;
  for (auto out_val : node_proto_->output()) {
    result.push_back(out_val);
  }
  return result;
}

// TODO(nsamar): Is this, and other functions here,
// really required to return nullptr or not? If not, change to return a
// const reference
const onnx::AttributeProto* OnnxNode::attribute(
    const std::string& attr_name) const {
  for (const auto& attr : node_proto_->attribute()) {
    if (attr.name() == attr_name) {
      return &attr;
    }
  }
  return nullptr;
}

int OnnxNode::output_channel_count() const {
  PANIC_IF(op_type() != "Conv");
  std::vector<Shape> input_shapes_vec = input_shapes();
  PANIC_IF(input_shapes_vec.size() < 2);
  const Shape& weights_shape = input_shapes_vec[1];
  return weights_shape[0];
}

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

// https://github.com/onnx/onnx/blob/main/docs/Operators.md
// ONNX IR specification says that the `kernel_shape` attribute
// MUST be present for `AveragePool` and `MaxPool`.
// However, `kernel_shape` MAY be ommitted from `Conv`; in this
// case the `kernel_shape` should be infered from input `W`.
Shape OnnxNode::kernel_shape() const {
  if (AttributeExists(ATTR_KERNEL_SHAPE)) {
    return Shape(optional_ints_attribute(ATTR_KERNEL_SHAPE));
  }
  std::vector<Shape> input_shapes_vec = input_shapes();
  // Infer input shape from weights
  if (input_shapes_vec.size() > 2) {
    std::cerr << "WARNING: ignoring biases of ConvLayer " << name() << "\n";
  }
  const Shape& weights_shape = input_shapes_vec[1];
  PANIC_IF(weights_shape[1] != input_shapes_vec[0][0],
           "ConvLayer mismatching number of channels", weights_shape,
           input_shapes_vec[0]);

  Shape kernel_shape = weights_shape.SubShape(2);
  return kernel_shape;
}

KernelAttributes OnnxNode::kernel() const {
  return KernelAttributes(kernel_shape(), strides(), padding());
}

std::string OnnxNode::op_type() const { return node_proto_->op_type(); }

std::string OnnxNode::name() const { return node_proto_->name(); }

}  // namespace janncy
