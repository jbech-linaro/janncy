#!/usr/bin/env python3

import os
from os.path import exists

# pip3
os.system("sudo apt-get install python3-pip")

# PyTorch
os.system("pip3 install torch")

# bazel
os.system("sudo apt install apt-transport-https curl gnupg")
os.system("curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg")
os.system("sudo mv bazel.gpg /etc/apt/trusted.gpg.d/")
os.system('echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list')
os.system("sudo apt update && sudo apt install bazel")

# clang
os.system("sudo apt-get install llvm-10")
os.system("sudo apt-get install clang-tools-10")
os.system("ln -s /usr/bin/clang++-10 /usr/bin/clang++")
os.system("ln -s /usr/bin/clang-10 /usr/bin/clang")

# protobuf
os.system("sudo apt-get install libprotobuf-dev protobuf-compiler")

# onnx
os.system("mkdir -p .dependencies")
os.system("cd .dependencies; git clone --recursive https://github.com/onnx/onnx.git")
os.system("sudo apt install graphviz libgraphviz-dev")

# graphviz
os.system("sudo apt install graphviz libgraphviz-dev")
