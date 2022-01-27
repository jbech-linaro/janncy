#include "include/onnx_parser.h"

int main(int argc, char** argv) {
  PANIC_IF(argc != 2,
           "Please provide filepath to *.onnx file as "
           "command-line argument!");
  auto nodes = janncy::ParseOnnxFile(argv[1]);
  for (const auto& node : nodes) {
    std::cout << node->name();
  }
}
