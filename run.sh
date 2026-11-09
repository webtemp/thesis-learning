#!/usr/bin/env bash
set -e
cd "$(dirname "$(realpath "$0")")"

case "$(uname -s)" in
  Darwin)
    CXX_BIN=/opt/homebrew/bin/g++
    NINJA=$(command -v ninja || echo /Applications/CLion.app/Contents/bin/ninja/mac/aarch64/ninja)
    ;;
  Linux)
    CXX_BIN=$(command -v g++)
    NINJA=$(command -v ninja)
    ;;
  *)
    echo "Unsupported OS: $(uname -s)" >&2
    exit 1
    ;;
esac

cmake -S . -B build-gcc -G Ninja -DCMAKE_MAKE_PROGRAM="$NINJA" -DCMAKE_CXX_COMPILER="$CXX_BIN" -DCMAKE_BUILD_TYPE=Debug
cmake --build build-gcc
./build-gcc/main "$@"
