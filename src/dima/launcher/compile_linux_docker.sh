# Compilation on Linux Docker

[ -d ../../../build/linux_docker/dima ] || mkdir ../../../build/linux_docker/dima
g++ -std=c++11 -O3 main.cpp -o ../../../build/linux_docker/dima/dima