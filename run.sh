#!/bin/bash

###############################################################################
# Build the various components of the Lanarts engine.
###############################################################################

set -e # Good practice -- exit completely on any bad exit code

# Set common variables and shell-script safety settings
source "scripts/common.sh"

###############################################################################
# Handle build flags.
###############################################################################

USE_LUAJIT=TRUE
BUILD_TYPE=Debug
BUILD_LINUX=TRUE
BUILD_WINDOWS=FALSE
CMAKE_COMMAND=cmake
MAKE_COMMAND=make
BUILD_ROOT="$(pwd)/build"
BUILD_FOLDER="$BUILD_ROOT/native"

if handle_flag "--vanilla-lua" || handle_flag "-vl" ; then
    USE_LUAJIT=FALSE
fi
if handle_flag "--optimize" || handle_flag "-O" ; then
    BUILD_TYPE=Debug
fi
if handle_flag "--mingw32" || handle_flag "-M" ; then 
    CMAKE_COMMAND=mingw32-cmake
    MAKE_COMMAND=mingw32-make
    BUILD_FOLDER="$BUILD_ROOT/mingw32"
    BUILD_LINUX=FALSE
    BUILD_WINDOWS=TRUE
fi

###############################################################################
# Run CMake. Specify configuration settings for MOAI.
###############################################################################

function run_cmake() {
    echo "Configuring build via CMake..." | colorify $LIGHT_BLUE
    $CMAKE_COMMAND \
        -DBUILD_LINUX=$BUILD_LINUX \
        -DBUILD_WINDOWS=$BUILD_WINDOWS \
        -DSDL_HOST=TRUE \
        -DMOAI_BOX2D=TRUE \
        -DMOAI_CHIPMUNK=FALSE \
        -DMOAI_CURL=TRUE \
        -DMOAI_CRYPTO=TRUE \
        -DMOAI_EXPAT=TRUE \
        -DMOAI_FREETYPE=TRUE \
        -DMOAI_JSON=TRUE \
        -DMOAI_JPG=TRUE \
        -DMOAI_MONGOOSE=TRUE \
        -DMOAI_LUAEXT=TRUE \
        -DMOAI_OGG=TRUE \
        -DMOAI_OPENSSL=TRUE \
        -DMOAI_SQLITE3=TRUE \
        -DMOAI_TINYXML=TRUE \
        -DMOAI_PNG=TRUE \
        -DMOAI_SFMT=TRUE \
        -DMOAI_VORBIS=TRUE \
        -DMOAI_UNTZ=TRUE \
        -DMOAI_LUAJIT=$USE_LUAJIT \
        -DMOAI_HTTP_CLIENT=TRUE \
        -DCMAKE_BUILD_TYPE=$BUILD_TYPE "$BUILD_ROOT"
    echo "Configured build via CMake." | colorify $YELLOW
}

###############################################################################
# Build Lanarts. Try to detect the number of cores for building with make.
###############################################################################

function build_engine(){
    mkdir -p "$BUILD_FOLDER"
    cd "$BUILD_FOLDER"

    run_cmake
    if handle_flag "--clean" ; then
        $MAKE_COMMAND clean
    fi

    # Configure amount of cores used
    if [[ -e /proc/cpuinfo ]] ; then
        cores=$(grep -c ^processor /proc/cpuinfo)
    else
        cores=4 # Guess -- may want to manually edit if above fails.
    fi

    echo "Building via generated Makefile..." | colorify $LIGHT_BLUE
    $MAKE_COMMAND V=1 -j$((cores+1))
    echo "Built via generated Makefile." | colorify $YELLOW
    cd ..
}

#   --force/-f: Do not build (use last successful compiled binary)
if ! handle_flag "-f" && ! handle_flag "--force" ; then
    if handle_flag "--verbose" || handle_flag "-v" ; then
       build_engine
    else
       build_engine > /dev/null
    fi
fi

###############################################################################
# Running the game. 
###############################################################################

function run_engine(){
    cd runtime
    if handle_flag "--gdb" || handle_flag "-g" ; then
        echo "Wrapping in GDB:" | colorify $YELLOW
        gdb -silent -ex=r --args ../$BUILD_FOLDER/src/engine $args
    else
        ../$BUILD_FOLDER/src/engine $args
    fi
    cd ..
}
