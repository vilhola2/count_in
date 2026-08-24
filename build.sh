#!/bin/bash

BUILD_TYPE=RELEASE
EXPORT_COMPILE_COMMANDS="OFF"
VERBOSE=0

for arg in "$@"; do
    case $arg in
        -d)
            BUILD_TYPE=DEBUG
            EXPORT_COMPILE_COMMANDS="ON"
            ;;
        -v)
            VERBOSE=1
            ;;
    esac
done

echo "Using build type: $BUILD_TYPE"

mkdir -p build
cd build
cmake  -DCMAKE_EXPORT_COMPILE_COMMANDS=$EXPORT_COMPILE_COMMANDS -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

if (( VERBOSE )) then
    cmake --build . --verbose
else
    cmake --build .
fi

if [ "$EXPORT_COMPILE_COMMANDS" = "ON" ]; then
    mv compile_commands.json ..
fi
