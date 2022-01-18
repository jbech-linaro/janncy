#!/bin/sh
CHECKS="-*,clang-diagnostic-*,clang-analyzer-*,bugprone*,modernize*,\
    performance*,-modernize-pass-by-value,-modernize-use-auto,\
    -modernize-use-using,cppcoreguidelines-*,\
    -cppcoreguidelines-pro-bounds-array-to-pointer-decay,google-*,misc-*, \
    performance-*,readability-*,-readability-implicit-bool-conversion, \
    -modernize-use-emplace"

SOURCE_FILES=$(find ./examples ./src -name "*.cc")
echo $SOURCE_FILES

clang-tidy -p=. --checks="$CHECKS" -header-filter='./src/.*\.h$' $SOURCE_FILES
