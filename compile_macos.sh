#!/bin/bash

# Compiling on macOS

# Config

PLATFORM=macos

COMPILE_GUI_MODULE=false   # Set it to true if you want to compile GUI Module
COMPILE_URL_MODULE=false   # Set it to true if you want to compile URL Module


# Preparation

echo "Preparing..."

[ -d build/$PLATFORM/modules/core ] || mkdir build/$PLATFORM/modules/core
[ -d build/$PLATFORM/modules/example ] || mkdir build/$PLATFORM/modules/example
[ -d build/$PLATFORM/modules/fileio ] || mkdir build/$PLATFORM/modules/fileio
[ -d build/$PLATFORM/modules/gui ] || mkdir build/$PLATFORM/modules/gui
[ -d build/$PLATFORM/modules/json ] || mkdir build/$PLATFORM/modules/json
[ -d build/$PLATFORM/modules/math ] || mkdir build/$PLATFORM/modules/math
[ -d build/$PLATFORM/modules/regex ] || mkdir build/$PLATFORM/modules/regex
[ -d build/$PLATFORM/modules/rl ] || mkdir build/$PLATFORM/modules/rl
[ -d build/$PLATFORM/modules/standardio ] || mkdir build/$PLATFORM/modules/standardio
[ -d build/$PLATFORM/modules/string ] || mkdir build/$PLATFORM/modules/string
[ -d build/$PLATFORM/modules/time ] || mkdir build/$PLATFORM/modules/time
[ -d build/$PLATFORM/modules/url ] || mkdir build/$PLATFORM/modules/url
[ -d build/$PLATFORM/modules/zip ] || mkdir build/$PLATFORM/modules/zip


# Compile main programme

echo "Compiling Dinfio main programme..."
g++ -std=c++11 -O3 src/main.cpp -o build/$PLATFORM/dinfio


# Compile modules

echo "Compiling module fileio..."
g++ -std=c++11 -O3 -dynamiclib src/modules/fileio/fileio.cpp -o build/$PLATFORM/modules/fileio/fileio.so

echo "Compiling module json..."
g++ -std=c++11 -O3 -dynamiclib src/modules/json/json.cpp -o build/$PLATFORM/modules/json/json.so

echo "Compiling module math..."
g++ -std=c++11 -O3 -dynamiclib src/modules/math/math.cpp -o build/$PLATFORM/modules/math/math.so

echo "Compiling module regex..."
g++ -std=c++11 -O3 -dynamiclib src/modules/regex/regex.cpp -o build/$PLATFORM/modules/regex/regex.so

echo "Compiling module rl..."
g++ -std=c++11 -O3 -dynamiclib src/modules/rl/rl.cpp -o build/$PLATFORM/modules/rl/rl.so

echo "Compiling module string..."
g++ -std=c++11 -O3 -dynamiclib src/modules/string/string.cpp -o build/$PLATFORM/modules/string/string.so

echo "Compiling module time..."
g++ -std=c++11 -O3 -dynamiclib src/modules/time/time.cpp -o build/$PLATFORM/modules/time/time.so

if [ "$COMPILE_URL_MODULE" = true ]; then
    echo "Compiling module url..."
    g++ -std=c++11 -O3 -dynamiclib src/modules/url/url.cpp -o build/$PLATFORM/modules/url/url.so -lcurl
    cp -f src/modules/url/*.fio build/$PLATFORM/modules/url/
fi

if [ "$COMPILE_GUI_MODULE" = true ]; then
    echo "Compiling module gui..."
    g++ -std=c++11 -O3 -dynamiclib src/modules/gui/gui.cpp -o build/$PLATFORM/modules/gui/gui.so `wx-config --cxxflags --libs core`
    cp -f src/modules/gui/*.fio build/$PLATFORM/modules/gui/
fi

cp -f src/modules/core/*.fio build/$PLATFORM/modules/core/
cp -f src/modules/standardio/*.fio build/$PLATFORM/modules/standardio/
cp -f src/modules/example/*.fio build/$PLATFORM/modules/example/
cp -f src/modules/fileio/*.fio build/$PLATFORM/modules/fileio/
cp -f src/modules/json/*.fio build/$PLATFORM/modules/json/
cp -f src/modules/math/*.fio build/$PLATFORM/modules/math/
cp -f src/modules/regex/*.fio build/$PLATFORM/modules/regex/
cp -f src/modules/rl/*.fio build/$PLATFORM/modules/rl/
cp -f src/modules/string/*.fio build/$PLATFORM/modules/string/
cp -f src/modules/time/*.fio build/$PLATFORM/modules/time/
cp -f src/modules/zip/*.fio build/$PLATFORM/modules/zip/


# Copy interactive and help

cp -f src/interactive/*.fio build/$PLATFORM/
cp -f src/help/*.fio build/$PLATFORM/

echo "Compilation done."