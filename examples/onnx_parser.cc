#include "include/onnx_parser.h"

#include "include/draw_dag.h"
#include "include/onnx_dag.h"
#include "include/onnx_dag_converter.h"

int main(int argc, char** argv) {
  PANIC_IF(argc != 2,
           "Please provide filepath to *.onnx file as "
           "command-line argument!");
  auto nodes = janncy::ParseOnnxFile(argv[1]);
  auto onnx_dag = MakeOnnxDag(std::move(nodes));
  auto nn = janncy::OnnxDagConverter::TranslateOnnxDag(onnx_dag);
  DrawDag(nn, "nn");
}
