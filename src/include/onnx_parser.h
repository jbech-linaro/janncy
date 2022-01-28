#ifndef JANNCY_ONNX_PARSER_H_
#define JANNCY_ONNX_PARSER_H_

#include <string>

#include "include/neural_network.h"

namespace janncy {

NeuralNetwork ParseOnnxFile(const std::string& onnx_filename);

}  // namespace janncy

#endif  // JANNCY_ONNX_PARSER_H_
