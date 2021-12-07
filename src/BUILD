cc_library(
        name = "Ciphertext",
        srcs = [ "Ciphertext.cpp" ],
        hdrs = [ "include/Ciphertext.hpp" ],
        deps = [ "//src:utils", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "Node",
        srcs = [ "Node.cpp" ],
        hdrs = [ "include/Node.hpp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "Graph",
        srcs = [ "Graph.cpp" ],
        hdrs = [ "include/Graph.hpp", ],
        deps = [ "//src:Node", "//src:CtOp", "//src:FlowNode", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "utils",
        srcs = [ "utils.cpp" ],
        hdrs = [ "include/utils.hpp", ],
        deps = [ "//src:Tensor", "//src:FlowNode", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "CtGraph",
        srcs = [ "CtGraph.cpp" ],
        hdrs = [ "include/CtGraph.hpp" ],
        deps = [ "//src:CtOp", "//src:CtAdd", "//src:CtMul", "//src:CtPtAdd", "//src:CtPtMul", "//src:CtRotate", "//src:CtInput", "//src:Graph", ],
        visibility = [ "//test:__pkg__", "//examples:__pkg__", ],
)

cc_library(
        name = "Flow",
        srcs = [ "Flow.cpp" ],
        hdrs = [ "include/Flow.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", "//src:ConvLayer", "//src:BatchNormalization", "//src:FullyConnected", "//src:Input", "//src:Graph", "//src:ReLU", "//src:AveragePool", "//src:Add", "//src:CtGraph", "//src:CtOp", ],
        visibility = [ "//test:__pkg__", "//examples:__pkg__", ],
)

cc_library(
        name = "CtOp",
        srcs = [ "CtOp.cpp" ],
        hdrs = [ "include/CtOp.hpp" ],
        deps = [ "//src:Node" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "FlowNode",
        srcs = [ "FlowNode.cpp" ],
        hdrs = [ "include/FlowNode.hpp" ],
        deps = [ "//src:Tensor", "//src:Node", "//src:CtTensor", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "Tensor",
        srcs = [ "Tensor.cpp" ],
        hdrs = [ "include/Tensor.hpp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "CtTensor",
        srcs = [ "CtTensor.cpp" ],
        hdrs = [ "include/CtTensor.hpp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "CtRotate",
        srcs = [ "CtRotate.cpp" ],
        hdrs = [ "include/CtRotate.hpp" ],
        deps = [ "//src:CtOp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "CtPtAdd",
        srcs = [ "CtPtAdd.cpp" ],
        hdrs = [ "include/CtPtAdd.hpp" ],
        deps = [ "//src:CtOp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "CtPtMul",
        srcs = [ "CtPtMul.cpp" ],
        hdrs = [ "include/CtPtMul.hpp" ],
        deps = [ "//src:CtOp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "CtMul",
        srcs = [ "CtMul.cpp" ],
        hdrs = [ "include/CtMul.hpp" ],
        deps = [ "//src:CtOp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "CtInput",
        srcs = [ "CtInput.cpp" ],
        hdrs = [ "include/CtInput.hpp" ],
        deps = [ "//src:CtOp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "CtAdd",
        srcs = [ "CtAdd.cpp" ],
        hdrs = [ "include/CtAdd.hpp" ],
        deps = [ "//src:CtOp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "Add",
        srcs = [ "Add.cpp" ],
        hdrs = [ "include/Add.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", "//src:CtGraph", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "Input",
        srcs = [ "Input.cpp" ],
        hdrs = [ "include/Input.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", "//src:CtGraph", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "FullyConnected",
        srcs = [ "FullyConnected.cpp" ],
        hdrs = [ "include/FullyConnected.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", "//src:CtGraph", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "BatchNormalization",
        srcs = [ "BatchNormalization.cpp" ],
        hdrs = [ "include/BatchNormalization.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", "//src:CtGraph", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "AveragePool",
        srcs = [ "AveragePool.cpp" ],
        hdrs = [ "include/AveragePool.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", "//src:utils", "//src:CtGraph", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "ConvLayer",
        srcs = [ "ConvLayer.cpp" ],
        hdrs = [ "include/ConvLayer.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", "//src:utils", "//src:CtGraph", ],
        visibility = [ "//test:__pkg__", ],
)

cc_library(
        name = "ReLU",
        srcs = [ "ReLU.cpp" ],
        hdrs = [ "include/ReLU.hpp" ],
        deps = [ "//src:Tensor", "//src:FlowNode", "//src:CtGraph", ],
        visibility = [ "//test:__pkg__", ],
)
