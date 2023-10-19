#!/bin/zsh

set -e

# cmake -S. -Bbuild
cmake --build build -j8

# pushd build && ctest && popd
