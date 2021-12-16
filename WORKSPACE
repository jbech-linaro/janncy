load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "graphviz",
    url = "https://gitlab.com/api/v4/projects/4207231/packages/generic/graphviz-releases/2.50.0/graphviz-2.50.0.tar.gz",
    strip_prefix = "graphviz-2.50.0",
    sha256 = "e17021a510bbd2770d4ca4b4eb841138122aaa5948f9e617e6bc12b4bac62e8d",
    build_file = "BUILD.graphviz",
)

http_archive(
    name = "com_google_protobuf",
    strip_prefix = "protobuf-3.19.1",
    urls = ["https://github.com/protocolbuffers/protobuf/archive/v3.19.1.tar.gz"],
)

git_repository(
    name = "gtest",
    remote = "https://github.com/google/googletest",
    branch = "v1.10.x",
)

new_git_repository(
    name = "onnx",
    remote = "https://github.com/onnx/onnx.git",
    tag = "v1.10.2",
    build_file = "BUILD.onnx",
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()
