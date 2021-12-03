#include <iostream>

#include "../src/include/Flow.hpp"

int main() {
    auto resnet = Flow();
    auto input_tensor = resnet.input(Tensor({3, 32, 32}));
    auto conv1 = resnet.conv_layer(input_tensor, Tensor({16, 3, 3}), 1);
    conv1->set_name("conv1");
    std::cout << resnet.str() << std::endl;
}
