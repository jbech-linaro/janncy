#ifndef ONNX_UTILS_H_
#define ONNX_UTILS_H_

#include <string>

#include <onnx/defs/tensor_proto_util.h>
#include <onnx/onnx_pb.h>
#include <onnx/proto_utils.h>

#include "include/kernel_attributes.h"
#include "include/onnx_dag.h"
#include "include/onnx_dag_converter.h"
#include "include/onnx_node.h"
#include "include/onnx_utils.h"
#include "include/panic.h"
#include "include/tensor.h"

namespace janncy {

namespace onnx_utils {

const std::string ONNX_ATTR_STRIDES = "strides";
const std::string ONNX_ATTR_PADDING = "pads";
const std::string ONNX_ATTR_AUTO_PAD = "auto_pad";
const std::string ONNX_ATTR_KERNEL_SHAPE = "kernel_shape";
const std::string ONNX_ATTR_AXIS = "axis";

bool file_exists(const std::string& filename);

const onnx::AttributeProto& attribute(const onnx::NodeProto& node_proto,
                                      const std::string& attr_name);

const onnx::AttributeProto& typed_attribute(
    const onnx::NodeProto& node_proto, const std::string& attr_name,
    const onnx::AttributeProto::AttributeType& attr_type);

int int_attribute(const onnx::NodeProto& node_proto,
                  const std::string& attr_name);

std::unique_ptr<onnx::ModelProto> ParseModel(const std::string& onnx_filename);

std::unique_ptr<OnnxNode> ReadInitializer(const onnx::TensorProto& ini);

OwnedOnnxNodeVec LoadInitializers(const onnx::GraphProto& graph_proto);

std::unique_ptr<OnnxNode> ReadInput(const onnx::ValueInfoProto& node_proto);

OwnedOnnxNodeVec LoadInputs(const onnx::GraphProto& graph_proto);

std::unique_ptr<OnnxNode> ReadReluLayer(const onnx::NodeProto& node_proto);

std::unique_ptr<OnnxNode> ReadAddLayer(const onnx::NodeProto& node_proto);

std::vector<int> optional_ints_attribute(const onnx::NodeProto& node_proto,
                                         const std::string& attr_name);
std::vector<int> strides(const onnx::NodeProto& node_proto);
std::vector<int> padding(const onnx::NodeProto& node_proto);
std::unique_ptr<OnnxNode> ReadConvLayer(const onnx::NodeProto& node_proto);

Shape kernel_shape(const onnx::NodeProto& node_proto);
KernelAttributes ReadKernelAttributes(const onnx::NodeProto& node_proto);
std::unique_ptr<OnnxNode> ReadMaxPoolLayer(const onnx::NodeProto& node_proto);

std::unique_ptr<OnnxNode> ReadAveragePoolLayer(
    const onnx::NodeProto& node_proto);

std::unique_ptr<OnnxNode> ReadGlobalAveragePoolLayer(
    const onnx::NodeProto& node_proto);

std::unique_ptr<OnnxNode> ReadFullyConnectedLayer(
    const onnx::NodeProto& node_proto);
std::unique_ptr<OnnxNode> ReadFlattenLayer(const onnx::NodeProto& node_proto);
std::unique_ptr<OnnxNode> ReadComputeNode(const onnx::NodeProto& node_proto);

OwnedOnnxNodeVec LoadComputeNodes(const onnx::GraphProto& graph_proto);

OwnedOnnxNodeVec MoveIntoFrom(OwnedOnnxNodeVec destination,
                              OwnedOnnxNodeVec source);
OwnedOnnxNodeVec ReadOnnxNodes(const onnx::GraphProto& graph_proto);

onnx::GraphProto FileToGraphProto(const std::string& onnx_filename);

OwnedOnnxNodeVec FileToOnnxNodeVec(const std::string& onnx_filename);

std::unordered_map<std::string, Tensor> ReadWeights(
    const onnx::GraphProto& graph_proto);

}  // namespace onnx_utils

}  // namespace janncy

#endif  // ONNX_UTILS_H_
