#include "include/onnx_parser.h"

#include <experimental/filesystem>
#include <fstream>
#include <memory>
#include <vector>

#include <onnx/defs/tensor_proto_util.h>
#include <onnx/onnx_pb.h>
#include <onnx/proto_utils.h>

#include "include/kernel_attributes.h"
#include "include/onnx_dag.h"
#include "include/onnx_dag_converter.h"
#include "include/onnx_node.h"
#include "include/onnx_utils.h"
#include "include/panic.h"

namespace janncy {

NeuralNetwork ParseOnnxFile(const std::string& onnx_filename) {
  auto onnx_node_vec = onnx_utils::FileToOnnxNodeVec(onnx_filename);
  auto onnx_dag = MakeOnnxDag(std::move(onnx_node_vec));
  auto nn = OnnxDagConverter::TranslateOnnxDag(onnx_dag);
  return nn;
}

}  // namespace janncy
