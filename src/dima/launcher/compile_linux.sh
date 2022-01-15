# Compilation on Linux x86_64

[ -d ../../../build/linux/dima ] || mkdir ../../../build/linux/dima
g++ -std=c++11 -O3 main.cpp -o ../../../build/linux/dima/dima