#!/bin/sh

clang-tidy -p=. --checks='-*,clang-diagnostic-*,clang-analyzer-*,bugprone*,modernize*,performance*,-modernize-pass-by-value,-modernize-use-auto,-modernize-use-using,cppcoreguidelines-*,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,google-*,misc-*,performance-*,readability-*,-readability-implicit-bool-conversion,-modernize-use-emplace' -header-filter='src/include/.*\.h$' src/*.cpp
