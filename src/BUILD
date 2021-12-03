cc_library(
        name = "Ciphertext",
        srcs = [ "Ciphertext.cpp" ],
        hdrs = [ "include/Ciphertext.hpp" ],
        deps = [ "//src:utils", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "utils",
        srcs = [ "utils.cpp" ],
        hdrs = [ "include/utils.hpp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "Flow",
        srcs = [ "Flow.cpp" ],
        hdrs = [ "include/Flow.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", "//src:ConvLayer", "//src:BatchNormalization", "//src:FullyConnected", "//src:Input" ],
        visibility = [ "//test:__pkg__", "//examples:__pkg__", ],
)

cc_library(
        name = "FlowNode",
        srcs = [ "FlowNode.cpp" ],
        hdrs = [ "include/FlowNode.hpp" ],
        deps = [ "//src:Tensor", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "Tensor",
        srcs = [ "Tensor.cpp" ],
        hdrs = [ "include/Tensor.hpp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "EncryptedTensor",
        srcs = [ "EncryptedTensor.cpp" ],
        hdrs = [ "include/EncryptedTensor.hpp" ],
        deps = [ "//src:Tensor", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "Input",
        srcs = [ "Input.cpp" ],
        hdrs = [ "include/Input.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "FullyConnected",
        srcs = [ "FullyConnected.cpp" ],
        hdrs = [ "include/FullyConnected.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "BatchNormalization",
        srcs = [ "BatchNormalization.cpp" ],
        hdrs = [ "include/BatchNormalization.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "AveragePool",
        srcs = [ "AveragePool.cpp" ],
        hdrs = [ "include/AveragePool.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "ConvLayer",
        srcs = [ "ConvLayer.cpp" ],
        hdrs = [ "include/ConvLayer.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "ReLU",
        srcs = [ "ReLU.cpp" ],
        hdrs = [ "include/ReLU.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", ],
        visibility = [ "//test:__pkg__", ],
)
