:: Compilation on Windows

if not exist "..\..\..\build\dima" (
    mkdir "..\..\..\build\dima"
)

g++ -std=c++11 -O3 main.cpp -o ..\..\..\build\dima\dima.exe