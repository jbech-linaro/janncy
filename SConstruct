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
# Don't forget to update installed.sh as well
clang_version = 10
cpp_version = 17

###############################################################################
# Paths
###############################################################################


build_dir = Path("build/")
src_dir = Path("src/")
test_dir = Path("test/")

clangpp_path = Path(f"/usr/bin/clang++-{clang_version}")

gtest_path = Path("googletest")
gtest_headers = Path("{}/googletest/include".format(gtest_path))
gtest_lib_path = Path("{}/build/lib".format(gtest_path))
libgtest = Path("{}/libgtest.a".format(gtest_lib_path))

heaan_path = Path("HEAAN")
heaanlib_path = Path("{}/HEAAN/lib/libHEAAN.a".format(heaan_path))

ntl_path = Path("ntl")
ntl_headers = Path("{}/include".format(ntl_path))
ntl_lib_path = Path("{}/src/ntl.a".format(ntl_path))

onnx_path = Path("onnx")

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
    cmd("protoc -I=onnx/onnx/ --cpp_out=onnx/onnx onnx/onnx/onnx.proto")
    cmd("protoc -I=onnx/ -I=onnx/onnx/ --cpp_out=onnx/onnx "
        "onnx/onnx/onnx-operators.proto")


def compile_heaan() -> None:
    cmd("cd {}/HEAAN/lib; make all".format(heaan_path))


def compile_gtest() -> None:
    if not os.path.exists(libgtest):
        logging.debug("Compiling {}".format(libgtest))
        cmd("mkdir -p {}/build".format(gtest_path))
        cmd("cd {}/build && cmake -DCMAKE_C_COMPILER='gcc' "
            "-DCMAKE_CXX_COMPILER='g++' .. && make".format(gtest_path))


def compile_ntl() -> None:
    if not os.path.exists(ntl_lib_path):
        cmd("cd {}/src && ./configure && make -j8".format(ntl_path))


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


def compile_dependencies() -> None:
    compile_gtest()
    compile_onnx()
    compile_ntl()
    compile_heaan()

###############################################################################
# Main
###############################################################################
logging.basicConfig(format='%(levelname)s[%(lineno)s]: %(message)s',
                    level=logging.DEBUG)

if COMMAND_LINE_TARGETS:
    if 'deps' in COMMAND_LINE_TARGETS:
        compile_dependencies()
        download_models()

    if 'update' in COMMAND_LINE_TARGETS:
        print(cmd("git submodule update --init --recursive"))
    sys.exit()

env = Environment(CXX=clangpp_path, ENV=os.environ)
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
onnx_cpps = [
        f"{onnx_path}/onnx/onnx.pb.cc",
        f"{onnx_path}/onnx/defs/tensor_proto_util.cc",
        f"{onnx_path}/onnx/defs/data_type_utils.cc",
        f"{onnx_path}/onnx/defs/shape_inference.cc", ]

onnx_parser_cpps = [ "examples/onnx_parser.cc" ] + onnx_cpps + Glob("src/*.cc")

#onnx_parser_cpps = [
#        "examples/onnx_parser.cc",
#        "onnx/onnx/onnx.pb.cc",
#        "onnx/onnx/defs/tensor_proto_util.cc",
#        "onnx/onnx/defs/data_type_utils.cc",
#        "onnx/onnx/defs/shape_inference.cc", ] + Glob("src/*.cc")
env.Append(CPPPATH=[ntl_headers])
env.Program(str(build_dir / "onnx_parser"), onnx_parser_cpps)

# Test
env.Program(str(build_dir / "tests"), Glob("test/*.cc") + onnx_cpps + Glob("src/*.cc"))
#env.Program(str(build_dir / "tests"), Glob("test/*.cc") + Glob("src/*.cc"))


#-onnx_parser_cpps = [ "examples/onnx_parser.cc", ".dependencies/onnx/onnx/onnx.pb.cc", ".dependencies/onnx/onnx/defs/tensor_proto_util.cc", ".dependencies/onnx/onnx/defs/data_type_utils.cc", ".dependencies/onnx/onnx/defs/shape_inference.cc", ] + Glob("src/*.cc")
#+onnx_cpps = [ ".dependencies/onnx/onnx/onnx.pb.cc", ".dependencies/onnx/onnx/defs/tensor_proto_util.cc", ".dependencies/onnx/onnx/defs/data_type_utils.cc", ".dependencies/onnx/onnx/defs/shape_inference.cc", ]
#+onnx_parser_cpps = [ "examples/onnx_parser.cc" ] + onnx_cpps + Glob("src/*.cc")
#env.Program(str(build_dir / "onnx_parser"), onnx_parser_cpps)
#-env.Program(str(build_dir / "tests"), Glob("test/*.cc") + Glob("src/*.cc"))
#+env.Program(str(build_dir / "tests"), Glob("test/*.cc") + onnx_cpps + Glob("src/*.cc"))

