#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include <onnx/defs/tensor_proto_util.h>
#include <onnx/onnx_pb.h>
#include <onnx/proto_utils.h>

#include "include/cipherfier.h"
#include "include/draw_graph.h"
#include "include/neural_network.h"
#include "include/onnx_graph.h"
#include "include/panic.h"
#include "include/shape.h"

using namespace janncy;

std::unique_ptr<onnx::ModelProto> ParseModel(const std::string& filepath) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  bool file_exists = std::experimental::filesystem::exists(filepath);
  PANIC_IF(!file_exists, "ONNX file does not exist!", filepath);

  std::ifstream in(filepath, std::ios::ate | std::ios::binary);
  std::streamsize size = in.tellg();
  in.seekg(0, std::ios::beg);

  std::vector<char> buffer(size);
  in.read(buffer.data(), size);
  auto model = std::make_unique<onnx::ModelProto>();
  ParseProtoFromBytes(model.get(), buffer.data(), size);

  return model;
}

int main(int argc, char** argv) {
  PANIC_IF(argc != 2,
           "Please provide filepath to *.onnx file as "
           "command-line argument!");
  auto model = ParseModel(argv[1]);
  std::cout << model->has_graph() << std::endl;
  PANIC_IF(!model->has_graph(), "Model does not have a graph!");

  auto graph = model->graph();

  auto flow = OnnxGraph::MakeFlow(graph);

  google::protobuf::ShutdownProtobufLibrary();
  janncy::DrawGraph(*flow, "flow");
  std::cerr << "Nodes in flow: " << flow->nodes().size() << "\n";
  /*
  CtGraph ct_graph = Cipherfier::Cipherfy(*flow);

  janncy::DrawGraph(ct_graph, "ct_graph");
  std::cerr << "Nodes in ct_graph: " << ct_graph.nodes().size() << "\n";
  */
}
