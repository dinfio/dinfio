/*
------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.2
------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2026. All Rights Reserved.
------------------------------------------------------------
 Platform: Linux, macOS, Windows
------------------------------------------------------------
 Dima: Dinfio Module Manager
------------------------------------------------------------
*/

#include <iostream>
#include <string>

using namespace std;

#ifdef __linux__
    const string __DINFIO_PATH__ = "/usr/local/dinfio/";
#elif __APPLE__
    const string __DINFIO_PATH__ = "/Library/Dinfio/3.2/";
#else
    const string __DINFIO_PATH__ = "C:/Dinfio/";
#endif

const string __DIMA_PATH__ = __DINFIO_PATH__ + "dima/";
const string __TOKEN__ = "55b9e2612764030c20b792960330d0f5";

int main(int argc, char* argv[]) {
    string args = "";

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        args += "\"" + arg + "\" ";
    }

    string command = __DINFIO_PATH__ + "dinfio \"" + __DIMA_PATH__ + "main.fio\" " + __TOKEN__ + " " + args;
    
    int result = system(command.c_str());
    return result;
}
