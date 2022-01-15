#include <iostream>

#include "include/Flow.hpp"
#include "include/flow_utils.hpp"

int main() {
  auto resnet = Flow();

  auto input_tensor = input(&resnet, {3, 8, 8});
  auto conv = conv_layer(&resnet, input_tensor, {8, 3, 3}, 1, 1);
  auto relu = relu(&resnet, conv);
  auto fc = fully_connected(&resnet, relu, {8, 3});
  batch_normalization(&resnet, fc);

  resnet.draw();

  /*
  auto ct_graph = resnet.cipherfy();
  ct_graph->draw("ct_graph");
  auto result = ct_graph->evaluate(
      std::vector<std::vector<double>>(3, std::vector<double>(32, 1)));
  for (auto& res : result) {
      for_each(res.begin(), res.end(),
               [&](auto x) { std::cout << x << " "; });
      std::cout << std::endl;
  }

  auto conv2_1 = conv2(resnet, input_tensor);
  auto conv2_2 = conv2(resnet, conv2_1);
  auto conv2_3 = conv2(resnet, conv2_2);

  auto conv3_1_out = conv3_1(resnet, conv2_3);
  auto conv3_2 = conv3(resnet, conv3_1_out);
  auto conv3_3 = conv3(resnet, conv3_2);

  // auto conv4_1_out = conv4_1(resnet, conv3_3);
  auto conv4_1_out = conv4_1(resnet, input_tensor);
  auto conv4_2 = conv4(resnet, conv4_1_out);
  auto conv4_3 = resnet.conv_layer(input_tensor, Tensor({8, 3, 3}), 1, true);
  auto r = resnet.reLU(conv4_3);
  auto ap = resnet.average_pool(r, Tensor({16, 4, 4}), 1, false);
  auto fc = resnet.fully_connected(ap, Tensor({16, 10}));
  */
}
