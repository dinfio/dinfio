rem Compilation on Windows

if not exist "..\..\..\build\windows\dima" (
    mkdir "..\..\..\build\windows\dima"
)

g++ -std=c++11 -O3 main.cpp -o ..\..\..\build\windows\dima\dima.exe