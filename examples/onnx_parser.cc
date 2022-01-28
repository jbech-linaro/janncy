#include "include/onnx_parser.h"

#include "include/draw_dag.h"
#include "include/panic.h"

int main(int argc, char** argv) {
  PANIC_IF(argc != 2,
           "Please provide filepath to *.onnx file as "
           "command-line argument!");
  auto nn = janncy::ParseOnnxFile(argv[1]);
  DrawDag(nn, "nn");
}
