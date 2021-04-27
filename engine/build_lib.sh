#!/bin/sh

echo "Building Engine Lib"

APP_NAME=engine

# DEBUG=true
MAIN_FILE="../src/main.cpp"
OSX_LD_FLAGS="-lsdl2 -framework Cocoa -framework Metal -lsdl2_image"

# CPLUS_INCLUDE_PATH="${CPLUS_INCLUDE_PATH:+${CPLUS_INCLUDE_PATH}:}$VULKAN_SDK/include;/usr/local/include"
CPLUS_INCLUDE_PATH="${CPLUS_INCLUDE_PATH:+${CPLUS_INCLUDE_PATH}:};/usr/local/include"
echo "CPLUS_INCLUDE_PATH: $CPLUS_INCLUDE_PATH\n"

BUILD_DIR="/build_lib"
OBJECT_DIR="/objdir"

SOURCE_MODULES="../../src/Engine/**.cpp"
SOURCE_OBJECTS=".${OBJECT_DIR}/*.o"

# TARGET
# --target=x86_64-unknown-linux-gnu

# DEBUG
# -gmodules to debug all modules
# DEBUG_OBJ="-g -gmodules -fsave-optimization-record=bitstream -fsave-optimization-record=yaml"
# DEBUG_MAIN="-g"
DEBUG_OBJ="-g0 -fno-debug-macro"
DEBUG_MAIN="-g0 -fno-debug-macro"

mkdir .${BUILD_DIR}
mkdir .${BUILD_DIR}${OBJECT_DIR}
pushd .${BUILD_DIR}
pushd .${OBJECT_DIR}

clang++ -std=c++1z $DEBUG_OBJ -Iincludes -c $SOURCE_MODULES
popd

clang++ -dynamiclib $OSX_LD_FLAGS -o lib${APP_NAME}.dylib -I ../src $SOURCE_OBJECTS
# clang++ -Wl,-undefined -Wl,dynamic_lookup -dynamiclib $OSX_LD_FLAGS -o lib${APP_NAME}.dylib -I ../src $SOURCE_OBJECTS
clang++ -std=c++1z $DEBUG_MAIN $OSX_LD_FLAGS lib${APP_NAME}.dylib $MAIN_FILE -Iincludes -o ${APP_NAME} $SOURCE_OBJECTS
popd

echo Finished Building Handmade Hero