#ifndef JANNCY_ONNX_PARSER_H_
#define JANNCY_ONNX_PARSER_H_

#include <memory>

#include "include/onnx_node.h"

namespace janncy {

std::vector<std::unique_ptr<OnnxNode>> ParseOnnxFile(
    const std::string& onnx_filename);

}  // namespace janncy

#endif  // JANNCY_ONNX_PARSER_H_
