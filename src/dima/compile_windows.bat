:: Compilation on Windows

@echo off

if not exist "..\..\build\dima" mkdir "..\..\build\dima"
if not exist "..\..\build\dima\helpers" mkdir "..\..\build\dima\helpers"

g++ -std=c++11 -O3 launcher\main.cpp -o ..\..\build\dima\dima.exe

xcopy /Y /Q main.fio ..\..\build\dima\ 1>NUL
xcopy /Y /Q helpers\*.fio ..\..\build\dima\helpers\ 1>NUL