:: Compiling on Windows

@echo off


:: Config

set CC=g++
set CXX=c++11


:: Set it to false if you don't want to compile the modules
set COMPILE_MODULES=true

:: Set it to true if you want to compile GUI Module
set COMPILE_GUI_MODULE=false
:: Set it to true if you want to compile URL Module
set COMPILE_URL_MODULE=false

:: Set it to your libcurl path
set LIBCURL_PATH=your_libcurl_path
:: Set it to your wxWidgets path
set WXWIDGETS_PATH=your_wxwidgets_path


:: Preparation

echo Preparing...

if not exist build\modules\core mkdir build\modules\core
if not exist build\modules\example mkdir build\modules\example
if not exist build\modules\fileio mkdir build\modules\fileio
if not exist build\modules\gui mkdir build\modules\gui
if not exist build\modules\json mkdir build\modules\json
if not exist build\modules\math mkdir build\modules\math
if not exist build\modules\regex mkdir build\modules\regex
if not exist build\modules\rl mkdir build\modules\rl
if not exist build\modules\standardio mkdir build\modules\standardio
if not exist build\modules\string mkdir build\modules\string
if not exist build\modules\time mkdir build\modules\time
if not exist build\modules\url mkdir build\modules\url
if not exist build\modules\zip mkdir build\modules\zip


:: Compile main programme

echo Compiling Dinfio main programme...
%CC% -std=%CXX% -O3 src\main.cpp -o build\dinfio.exe


:: Compile modules

if %COMPILE_MODULES%==true (
    echo Compiling module fileio...
    %CC% -O3 -shared src\modules\fileio\fileio.cpp -o build\modules\fileio\fileio.dll

    echo Compiling module json...
    %CC% -std=%CXX% -O3 -shared src\modules\json\json.cpp -o build\modules\json\json.dll

    echo Compiling module math...
    %CC% -std=%CXX% -O3 -shared src\modules\math\math.cpp -o build\modules\math\math.dll

    echo Compiling module regex...
    %CC% -std=%CXX% -O3 -shared src\modules\regex\regex.cpp -o build\modules\regex\regex.dll

    echo Compiling module rl...
    %CC% -std=gnu++11 -O3 -shared src\modules\rl\rl.cpp -o build\modules\rl\rl.dll

    echo Compiling module string...
    %CC% -std=%CXX% -O3 -shared src\modules\string\string.cpp -o build\modules\string\string.dll

    echo Compiling module time...
    %CC% -std=%CXX% -O3 -shared -D _WIN32_WINNT=0x0501 src\modules\time\time.cpp -o build\modules\time\time.dll

    if %COMPILE_URL_MODULE%==true (
        echo Compiling module url...
        %CC% -std=%CXX% -O3 -shared src\modules\url\url.cpp -o build\modules\url\url.dll -I"%LIBCURL_PATH%\lib\include" -lcurl -L"%LIBCURL_PATH%\lib\lib"
        xcopy /Y /Q src\modules\url\*.fio build\modules\url\
    )

    if %COMPILE_GUI_MODULE%==true (
        echo Compiling module gui...
        %CC% -O3 -shared src\modules\gui\gui.cpp -o build\modules\gui\gui.dll -I"%WXWIDGETS_PATH%\include\wx-3.1" -I"%WXWIDGETS_PATH%\lib\wx\include\msw-unicode-3.1" -L"%WXWIDGETS_PATH%\lib" -lwx_mswu_core-3.1 -llibwx_baseu-3.1
        xcopy /Y /Q src\modules\gui\*.fio build\modules\gui\
    )

    xcopy /Y /Q src\modules\core\*.fio build\modules\core\
    xcopy /Y /Q src\modules\standardio\*.fio build\modules\standardio\
    xcopy /Y /Q src\modules\example\*.fio build\modules\example\
    xcopy /Y /Q src\modules\fileio\*.fio build\modules\fileio\
    xcopy /Y /Q src\modules\json\*.fio build\modules\json\
    xcopy /Y /Q src\modules\math\*.fio build\modules\math\
    xcopy /Y /Q src\modules\regex\*.fio build\modules\regex\
    xcopy /Y /Q src\modules\rl\*.fio build\modules\rl\
    xcopy /Y /Q src\modules\string\*.fio build\modules\string\
    xcopy /Y /Q src\modules\time\*.fio build\modules\time\
    xcopy /Y /Q src\modules\zip\*.fio build\modules\zip\
    xcopy /Y /Q src\modules\zip\*.exe build\modules\zip\
)


:: Copy interactive and help

xcopy /Y /Q src\interactive\*.fio build\
xcopy /Y /Q src\help\*.fio build\

echo Compilation done.