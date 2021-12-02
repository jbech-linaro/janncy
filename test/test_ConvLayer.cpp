#include "gtest/gtest.h"

#include "src/include/ConvLayer.hpp"
#include "src/include/Tensor.hpp"

TEST(ConvLayerTest, Shapes) {
    auto input_tensor = Tensor({3, 16, 16});
    auto filter = Tensor({1, 3, 3, 3});
    auto conv_layer = ConvLayer(input_tensor, filter, 1);
    auto expected = std::vector<int>{1, 14, 14};
    auto actual = conv_layer.output_tensor().shape();
    EXPECT_EQ(expected, actual);
}

TEST(ConvLayerTest, Strides) {
    auto input_tensor = Tensor({3, 16, 16});
    auto filter = Tensor({1, 3, 3, 3});
    auto conv_layer = ConvLayer(input_tensor, filter, 2);
    auto expected = std::vector<int>{1, 7, 7};
    auto actual = conv_layer.output_tensor().shape();
    EXPECT_EQ(expected, actual);
}
