#!/usr/bin/env python3

from pathlib import Path
import subprocess
import os
import sys
import torch

build_dir = Path("build/")
src_dir = Path("src/")
test_dir = Path("test/")
clang_version = 10
cpp_version = 17
install_cmd = "sudo apt-get install -y"
clangpp_path = Path(f"/usr/bin/clang++-{clang_version}")
clang_path = Path(f"/usr/bin/clang-{clang_version}")
onnx_path = Path(".dependencies/onnx")
heaanlib_path = Path(".dependencies/HEAAN/HEAAN/lib/libHEAAN.a")
gtest_path = Path(".dependencies/googletest")
gtest_headers = Path("{}/googletest/include".format(gtest_path))
gtest_lib_path = Path("{}/build/lib".format(gtest_path))
libgtest = Path("{}/libgtest.a".format(gtest_lib_path))
ntl_path = Path(".dependencies/ntl")
ntl_headers = Path("{}/include".format(ntl_path))
ntl_lib_path = Path("{}/src/ntl.a".format(ntl_path))
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
    if os.path.exists(onnx_path):
        return
    cmd("mkdir -p .dependencies")
    cmd("cd .dependencies; git clone --recursive https://github.com/onnx/onnx.git")
    cmd("protoc -I=.dependencies/onnx/onnx/ --cpp_out=.dependencies/onnx/onnx .dependencies/onnx/onnx/onnx.proto")
    cmd("protoc -I=.dependencies/onnx/ -I=.dependencies/onnx/onnx/ --cpp_out=.dependencies/onnx/onnx .dependencies/onnx/onnx/onnx-operators.proto")

def install_heaan() -> None:
    if os.path.exists(heaanlib_path):
        cmd("cd .dependencies/HEAAN; git pull; cd HEAAN/lib; make all")
    cmd("mkdir -p .dependencies")
    if not os.path.exists(".dependencies/HEAAN"):
        cmd("cd .dependencies; git clone git@github.com:n-samar/HEAAN.git; cd HEAAN")
        cmd("git config pull.ff only")
    cmd("cd .dependencies/HEAAN/HEAAN/lib; make all")

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
    if not os.path.exists("{}/README.md".format(gtest_path)):
        cmd("mkdir -p .dependencies")
        cmd("cd .dependencies && git clone https://github.com/google/googletest.git")

    if not os.path.exists(libgtest):
        print("Compiling {}".format(libgtest))
        cmd("mkdir -p {}/build".format(gtest_path))
        cmd("cd {}/build && cmake -DCMAKE_C_COMPILER='gcc' -DCMAKE_CXX_COMPILER='g++' .. && make".format(gtest_path))

def install_ntl() -> None:
    if not os.path.exists(ntl_path):
        cmd("mkdir -p .dependencies && cd .dependencies && git clone git@github.com:libntl/ntl.git")
    if not os.path.exists(ntl_lib_path):
        cmd("cd .dependencies/ntl/src && ./configure && make -j8")

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

def install_cmake() -> None:
    install_if_missing("cmake")

def install_dependencies() -> None:
    install_cmake()
    install_clang()
    install_protobuf()
    install_graphviz()
    install_gtest()
    install_onnx()
    install_ntl()
    install_heaan()
    install_torch()
    download_models()

install_dependencies()

env = Environment(CXX = f'/usr/bin/clang++-{clang_version}', ENV = os.environ)
env.VariantDir(build_dir, src_dir, duplicate=0)
env.Append(CPPFLAGS = [ "-fsanitize=address", "-O3", ])
env.Append(CPPFLAGS = [ "-ggdb", "-fno-omit-frame-pointer", "-g", f"-std=c++{cpp_version}", "-Wall", "-DONNX_NAMESPACE=onnx", ])
env.Append(CPPPATH = [ onnx_path, src_dir, heaanlib_path.parent.parent.parent, gtest_headers ])
env.Append(LIBS = [ "HEAAN", "asan", "stdc++fs", "pthread", "ntl", "gmp", "m", "cgraph", "gvc", "protobuf", "gtest_main", "gtest", ])
env.Append( LIBPATH = [ heaanlib_path.parent, gtest_lib_path ])
env.Tool('compilation_db')
env.CompilationDatabase()

onnx_parser_cpps = [ "examples/onnx_parser.cc", ".dependencies/onnx/onnx/onnx.pb.cc", ".dependencies/onnx/onnx/defs/tensor_proto_util.cc", ".dependencies/onnx/onnx/defs/data_type_utils.cc", ".dependencies/onnx/onnx/defs/shape_inference.cc", ] + Glob("src/*.cc")
env.Append(CPPPATH = [ ntl_headers ])
env.Program(str(build_dir / "onnx_parser"), onnx_parser_cpps)

env.Program(str(build_dir / "tests"), Glob("test/*.cc") + Glob("src/*.cc"))
