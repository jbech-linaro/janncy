#include "include/onnx_parser.h"

#include "include/onnx_dag.h"

int main(int argc, char** argv) {
  PANIC_IF(argc != 2,
           "Please provide filepath to *.onnx file as "
           "command-line argument!");
  auto nodes = janncy::ParseOnnxFile(argv[1]);
  MakeOnnxDag(std::move(nodes));
}
