cc_library(
        name = "onnx_proto",
        srcs = [ ".dependencies/onnx/onnx/onnx.pb.cc", ],
        hdrs = [ ".dependencies/onnx/onnx/onnx.pb.h", ],
        copts = [ "-I.dependencies/onnx/", ],
        linkopts = [ "-lprotobuf", ],
        visibility = [ "//visibility:public", ],
)
