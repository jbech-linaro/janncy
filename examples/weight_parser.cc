#include "include/onnx_utils.h"
#include "include/panic.h"
#include "include/weight_manager.h"

int main(int argc, char** argv) {
  PANIC_IF(argc != 2,
           "Please provide filepath to *.onnx file as "
           "command-line argument!");
  janncy::WeightManager(janncy::onnx_utils::ReadWeights(
      janncy::onnx_utils::FileToGraphProto(argv[1])));
}
