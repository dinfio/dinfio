#!/bin/bash

# Compiling on Linux Docker

# Config

CC=g++
CXX=c++11

COMPILE_MODULES=true       # Set it to false if you don't want to compile the modules
COMPILE_URL_MODULE=false   # Set it to true if you want to compile URL Module


# Preparation

echo "Preparing..."

[ -d build/modules/core ] || mkdir build/modules/core
[ -d build/modules/example ] || mkdir build/modules/example
[ -d build/modules/fileio ] || mkdir build/modules/fileio
[ -d build/modules/json ] || mkdir build/modules/json
[ -d build/modules/math ] || mkdir build/modules/math
[ -d build/modules/regex ] || mkdir build/modules/regex
[ -d build/modules/rl ] || mkdir build/modules/rl
[ -d build/modules/standardio ] || mkdir build/modules/standardio
[ -d build/modules/string ] || mkdir build/modules/string
[ -d build/modules/time ] || mkdir build/modules/time
[ -d build/modules/url ] || mkdir build/modules/url
[ -d build/modules/zip ] || mkdir build/modules/zip


# Compile main programme

echo "Compiling Dinfio main programme..."
$CC -std=$CXX -O3 -w src/main.cpp -ldl -o build/dinfio


# Compile modules

if [ "$COMPILE_MODULES" = true ]; then
    echo "Compiling module fileio..."
    $CC -std=$CXX -O3 -w -fPIC -shared src/modules/fileio/fileio.cpp -o build/modules/fileio/fileio.so

    echo "Compiling module json..."
    $CC -std=$CXX -O3 -w -fPIC -shared src/modules/json/json.cpp -o build/modules/json/json.so

    echo "Compiling module math..."
    $CC -std=$CXX -O3 -w -fPIC -shared src/modules/math/math.cpp -o build/modules/math/math.so

    echo "Compiling module regex..."
    $CC -std=$CXX -O3 -w -fPIC -shared src/modules/regex/regex.cpp -o build/modules/regex/regex.so

    echo "Compiling module rl..."
    $CC -std=$CXX -O3 -w -fPIC -shared src/modules/rl/rl.cpp -o build/modules/rl/rl.so

    echo "Compiling module string..."
    $CC -std=$CXX -O3 -w -fPIC -shared src/modules/string/string.cpp -o build/modules/string/string.so

    echo "Compiling module time..."
    $CC -std=$CXX -O3 -w -fPIC -shared src/modules/time/time.cpp -o build/modules/time/time.so

    if [ "$COMPILE_URL_MODULE" = true ]; then
        echo "Compiling module url..."
        $CC -std=$CXX -O3 -w -fPIC -shared src/modules/url/url.cpp -o build/modules/url/url.so -lcurl
        cp -f src/modules/url/*.fio build/modules/url/
    fi

    cp -f src/modules/core/*.fio build/modules/core/
    cp -f src/modules/standardio/*.fio build/modules/standardio/
    cp -f src/modules/example/*.fio build/modules/example/
    cp -f src/modules/fileio/*.fio build/modules/fileio/
    cp -f src/modules/json/*.fio build/modules/json/
    cp -f src/modules/math/*.fio build/modules/math/
    cp -f src/modules/regex/*.fio build/modules/regex/
    cp -f src/modules/rl/*.fio build/modules/rl/
    cp -f src/modules/string/*.fio build/modules/string/
    cp -f src/modules/time/*.fio build/modules/time/
    cp -f src/modules/zip/*.fio build/modules/zip/
fi


# Copy interactive and help

cp -f src/interactive/*.fio build/
cp -f src/help/*.fio build/

echo "Compilation done."
