# Compilation on Linux ARMv7

[ -d ../../../build/linux_armv7/dima ] || mkdir ../../../build/linux_armv7/dima
g++ -std=c++11 -O3 main.cpp -o ../../../build/linux_armv7/dima/dima