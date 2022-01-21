#!/usr/bin/env python3

from pathlib import Path
import logging
import os
import subprocess
import sys
import torch

###############################################################################
# Configuration
###############################################################################


install_cmd = "sudo apt-get install -y"
clang_version = 10
cpp_version = 17

# apt-get packages
packages = [f"clang-tools-{clang_version}",
            f"cmake llvm-{clang_version}",
            "graphviz",
            "libgraphviz-dev",
            "libjpeg-dev",
            "libprotobuf-dev",
            "protobuf-compiler",
            "python3-pip",
            "zlib1g-dev",
            ]

# Python pip packages
pip_packages = ["image",
                "numpy"
                # "pep8",
                "scons",
                "torch",
                # "virtualenv",
                ]
###############################################################################
# Paths
###############################################################################


build_dir = Path("build/")
src_dir = Path("src/")
test_dir = Path("test/")

clangpp_path = Path(f"/usr/bin/clang++-{clang_version}")
clang_path = Path(f"/usr/bin/clang-{clang_version}")

onnx_path = Path(".dependencies/onnx")
heaanlib_path = Path(".dependencies/HEAAN/HEAAN/lib/libHEAAN.a")

gtest_path = Path("googletest")
gtest_headers = Path("{}/googletest/include".format(gtest_path))
gtest_lib_path = Path("{}/build/lib".format(gtest_path))
libgtest = Path("{}/libgtest.a".format(gtest_lib_path))

ntl_path = Path(".dependencies/ntl")
ntl_headers = Path("{}/include".format(ntl_path))
ntl_lib_path = Path("{}/src/ntl.a".format(ntl_path))

###############################################################################
# Helpers
###############################################################################


def cmd(cmd_str: str) -> str:
    logging.debug("Run command: {}".format(cmd_str))
    result = subprocess.run(cmd_str, shell=True, stdout=subprocess.PIPE,
                            encoding="utf-8")
    if result.returncode != 0:
        logging.error(f"Command `{cmd_str}' failed with exit code "
                      "{result.returncode}!")
        raise SystemExit()
    logging.debug(result.stdout)
    return result.stdout

###############################################################################
# Locally installed dependencies
###############################################################################


def compile_onnx() -> None:
    cmd("protoc -I=.dependencies/onnx/onnx/ "
        "--cpp_out=.dependencies/onnx/onnx "
        ".dependencies/onnx/onnx/onnx.proto")
    cmd("protoc -I=.dependencies/onnx/ -I=.dependencies/onnx/onnx/ "
        "--cpp_out=.dependencies/onnx/onnx "
        ".dependencies/onnx/onnx/onnx-operators.proto")


def compile_heaan() -> None:
    cmd("cd .dependencies/HEAAN/HEAAN/lib; make all")


def compile_gtest() -> None:
    if not os.path.exists(libgtest):
        logging.debug("Compiling {}".format(libgtest))
        cmd("mkdir -p {}/build".format(gtest_path))
        cmd("cd {}/build && cmake -DCMAKE_C_COMPILER='gcc' "
            "-DCMAKE_CXX_COMPILER='g++' .. && make".format(gtest_path))


def compile_ntl() -> None:
    if not os.path.exists(ntl_lib_path):
        cmd("cd .dependencies/ntl/src && ./configure && make -j8")


def download_models() -> None:
    cmd("mkdir -p .pytorch")
    pytorch_path = Path(".pytorch")

    # available models: https://modelzoo.co/model/pretrained-modelspytorch
    models = ["resnet18", "resnet152", "resnet50", "densenet121", "vgg11",
              "vgg13"]

    for model_name in models:
        if not os.path.exists(pytorch_path / f"{model_name}.onnx"):
            logging.debug(f"Downloading {model_name} weights...")
            model = torch.hub.load("pytorch/vision:v0.10.0",
                                   model_name, pretrained=True)
            torch.onnx.export(model, torch.randn(1, 3, 224, 224),
                              pytorch_path / f"{model_name}.onnx")


def install_dependencies() -> None:
    install_str = "{} {}".format(install_cmd, " ".join(packages))
    logging.info("This will need sudo rights, since we're about to install\
                 distro packages")
    # cmd(install_str)
    #  TODO
    # cmd("pip install image torch numpy")
    # download_models()


def compile_dependencies() -> None:
    compile_gtest()
    # compile_onnx()
    # compile_ntl()
    # compile_heaan()


###############################################################################
# Main
###############################################################################
logging.basicConfig(format='%(levelname)s[%(lineno)s]: %(message)s',
                    level=logging.DEBUG)

if COMMAND_LINE_TARGETS:
    if 'setup' in COMMAND_LINE_TARGETS:
        install_dependencies()

    if 'deps' in COMMAND_LINE_TARGETS:
        compile_dependencies()

    if 'update' in COMMAND_LINE_TARGETS:
        print(cmd("git submodule update --init --recursive"))
    sys.exit()

env = Environment(CXX=f'/usr/bin/clang++-{clang_version}', ENV=os.environ)
env.VariantDir(build_dir, src_dir, duplicate=0)

# Compiler flags
env.Append(CPPFLAGS=["-fsanitize=address", "-O3"])
env.Append(CPPFLAGS=["-ggdb", "-fno-omit-frame-pointer", "-g",
                     f"-std=c++{cpp_version}", "-Wall",
                     "-DONNX_NAMESPACE=onnx"])

# Include folders
env.Append(CPPPATH=[onnx_path, src_dir, heaanlib_path.parent.parent.parent,
                    gtest_headers])

# Libraries
env.Append(LIBS=["HEAAN", "asan", "stdc++fs", "pthread", "ntl", "gmp", "m",
                 "cgraph", "gvc", "protobuf", "gtest_main", "gtest"])

# Library paths
env.Append(LIBPATH=[heaanlib_path.parent, gtest_lib_path])

env.Tool('compilation_db')
env.CompilationDatabase()

# onnx
onnx_parser_cpps = [
        "examples/onnx_parser.cc",
        ".dependencies/onnx/onnx/onnx.pb.cc",
        ".dependencies/onnx/onnx/defs/tensor_proto_util.cc",
        ".dependencies/onnx/onnx/defs/data_type_utils.cc",
        ".dependencies/onnx/onnx/defs/shape_inference.cc", ] + Glob("src/*.cc")
env.Append(CPPPATH=[ntl_headers])
env.Program(str(build_dir / "onnx_parser"), onnx_parser_cpps)

# Test
env.Program(str(build_dir / "tests"), Glob("test/*.cc") + Glob("src/*.cc"))
