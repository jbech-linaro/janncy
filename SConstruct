#!/usr/bin/env python3

from pathlib import Path
import subprocess
import os
import sys
import torch

build_dir = Path("build/")
src_dir = Path("src/")
test_dir = Path("test/")
gtest_dir = Path("/usr/gtest/include")
clang_version = 10
cpp_version = 17
install_cmd = "sudo apt-get install -y"
clangpp_path = Path(f"/usr/bin/clang++-{clang_version}")
clang_path = Path(f"/usr/bin/clang-{clang_version}")
onnx_path = Path(".dependencies/onnx")
pip3_list_path = Path(".pip3_list")

def cmd_allow_fail(cmd_str : str) -> str:
    result = subprocess.run(cmd_str, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, encoding="utf-8")
    return result

def cmd(cmd_str: str) -> str:
    result = subprocess.run(cmd_str, shell=True, stdout=subprocess.PIPE, encoding="utf-8")
    if result.returncode != 0:
        print(f"Command `{cmd_str}' failed with exit code {result.returncode}!")
        raise SystemExit()
    return result.stdout

def get_pip3_list() -> str:
    if os.path.exists(pip3_list_path):
        return pip3_list_path.open().read()
    result = cmd("pip3 list")
    with open(pip3_list_path, "w") as f:
        f.write(result)
    return result

pip3_list = get_pip3_list()

def is_library_installed(library_name: str) -> None:
    result = cmd_allow_fail(f"dpkg -L {library_name}")
    return not ("is not installed" in str(result))

def install_if_missing(package_name: str) -> None:
    if not is_library_installed(package_name):
        cmd(f"{install_cmd} {package_name}")

def is_pip3_package_installed(package_name: str) -> bool:
    global pip3_list
    return package_name in pip3_list

def pip3_if_missing(package_name: str) -> None:
    if not is_pip3_package_installed(package_name):
        cmd(f"pip3 install {package_name}")

        with open(pip3_list_path, "w") as f:
            f.write(cmd("pip3 list"))

def install_clang() -> None:
    install_if_missing(f"llvm-{clang_version}")
    install_if_missing(f"clang-tools-{clang_version}")

def install_protobuf() -> None:
    install_if_missing("libprotobuf-dev")
    install_if_missing("protobuf-compiler")

def install_onnx() -> None:
    cmd("mkdir -p .dependencies")
    cmd("cd .dependencies; git clone --recursive https://github.com/onnx/onnx.git")
    cmd("protoc -I=.dependencies/onnx/onnx/ --cpp_out=.dependencies/onnx/onnx .dependencies/onnx/onnx/onnx.proto")
    cmd("protoc -I=.dependencies/onnx/ -I=.dependencies/onnx/onnx/ --cpp_out=.dependencies/onnx/onnx .dependencies/onnx/onnx/onnx-operators.proto")

def install_graphviz() -> None:
    install_if_missing("graphviz")
    install_if_missing("libgraphviz-dev")

def install_torch() -> None:
    # pip3
    install_if_missing("python3-pip")
    # pillow
    install_if_missing("libjpeg-dev")
    install_if_missing("zlib1g-dev")
    pip3_if_missing("image")
    # PyTorch
    pip3_if_missing("torch")
    # numpy
    pip3_if_missing("numpy")

def install_gtest() -> None:
    if os.path.exists("/usr/lib/libgtest.a"):
        return
    install_if_missing("libgtest-dev")
    install_if_missing("cmake")
    cmd("cd /usr/src/gtest; sudo cmake CMakeLists.txt")
    cmd("cd /usr/src/gtest; sudo make")
    cmd("cd /usr/src/gtest; sudo cp *.a /usr/lib")

def download_models() -> None:
    cmd("mkdir -p .pytorch")
    pytorch_path = Path(".pytorch")

    # available models: https://modelzoo.co/model/pretrained-modelspytorch
    models = [ "resnet18", "resnet152", "resnet50", "densenet121", "vgg11", "vgg13" ]

    for model_name in models:
        if not os.path.exists(pytorch_path / f"{model_name}.onnx"):
            print(f"Downloading {model_name} weights...")
            model = torch.hub.load("pytorch/vision:v0.10.0", model_name, pretrained=True)
            torch.onnx.export(model, torch.randn(1, 3, 224, 224), pytorch_path / f"{model_name}.onnx")

def install_dependencies() -> None:
    install_clang()
    install_protobuf()
    install_graphviz()
    if not os.path.exists(onnx_path):
        install_onnx()
    install_torch()
    install_gtest()
    download_models()

install_dependencies()

env = Environment(CXX = f'/usr/bin/clang++-{clang_version}', ENV = os.environ)
env.VariantDir(build_dir, src_dir, duplicate=0)
env.Append(CPPFLAGS = [ "-g", f"-std=c++{cpp_version}", "-Wall", "-DONNX_NAMESPACE=onnx", ])
env.Append(CPPPATH = [ onnx_path, src_dir, gtest_dir, ])
env.Append(LIBS = [ "stdc++fs", "pthread", "cgraph", "gvc", "protobuf", "gtest_main", "gtest", ])

onnx_parser_cpps = [ "examples/OnnxParser.cpp", ".dependencies/onnx/onnx/onnx.pb.cc", ".dependencies/onnx/onnx/defs/tensor_proto_util.cc", ".dependencies/onnx/onnx/defs/data_type_utils.cc", ".dependencies/onnx/onnx/defs/shape_inference.cc", ] + Glob("src/*.cpp")
env.Program(str(build_dir / "onnx_parser"), onnx_parser_cpps)

env.Program(str(build_dir / "tests"), Glob("test/*.cpp"))
