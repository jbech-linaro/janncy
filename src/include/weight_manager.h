#ifndef WEIGHT_MANAGER_H_
#define WEIGHT_MANAGER_H_

#include <iostream>
#include <string>
#include <unordered_map>

#include <onnx/defs/tensor_proto_util.h>
#include <onnx/onnx_pb.h>
#include <onnx/proto_utils.h>

#include "include/tensor.h"

namespace janncy {

class WeightManager {
 public:
  WeightManager(std::unordered_map<std::string, Tensor> weight_map)
      : weight_map_(weight_map) {
    for (const auto& weight : weight_map_) {
      std::cout << weight.first << ": " << weight.second.shape() << std::endl;
    }
  }

 private:
  std::unordered_map<std::string, Tensor> weight_map_;
};

}  // namespace janncy

#endif  // WEIGHT_MANAGER_H_
