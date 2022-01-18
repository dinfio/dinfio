# Compilation on Linux x86_64, ARMv7, Docker

[ -d ../../build/dima ] || mkdir ../../build/dima
[ -d ../../build/dima/helpers ] || mkdir ../../build/dima/helpers

g++ -std=c++11 -O3 launcher/main.cpp -o ../../build/dima/dima

cp -f main.fio ../../build/dima/
cp -f helpers/*.fio ../../build/dima/helpers/