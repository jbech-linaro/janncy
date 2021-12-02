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
