# Building Dinfio

Before building Dinfio, please make sure you have all the [required build tools and libraries](#required-build-tools-and-libraries) installed.

## Getting the Source Code

Download the source code by cloning the git repository:
``` sh
$ git clone https://github.com/dinfio/dinfio.git
```

After the source code downloaded, go to directory `dinfio`:
``` sh
$ cd dinfio
```

## Configuring and Compiling

Open file [`src/header.h`](src/header.h), and point to  `__DINFIO_PATH__` constant (at line 45 or 52 or 59, depending on your platform):

``` cpp
const string __DINFIO_PATH__ = "/usr/local/dinfio/";
```

Change the constant value with your build path (absolute path), for example:

``` cpp
const string __DINFIO_PATH__ = "/home/sweet/Documents/dinfio/build/";
```

> Additionally, please see the [notes](#notes) below if you want to opt-in module `url` and/or `gui` in the compilation process.

<br>

And compile:

- On Linux x86_64:

    ``` sh
    $ ./compile_linux.sh
    ```
- On Linux ARMv7:

    ``` sh
    $ ./compile_linux_armv7.sh
    ```
- On Linux Docker:

    ``` sh
    $ ./compile_linux_docker.sh
    ```
- On macOS:

    ``` sh
    $ ./compile_macos.sh
    ```
- On Windows:

    ```
    > compile_windows.bat
    ```

Once it is compiled, go to your build path (`cd build/`), and run Dinfio executable:

``` sh
$ ./dinfio -v
```

If you see the Dinfio version, then Dinfio is successfully compiled.

## Testing the Modules

You can run test below to make sure all of the modules are well compiled:

``` sh
$ ./dinfio ../tests/modules.fio
```

If you do not see any error message, then the modules are successfully and well compiled.

Please note that module `url` and `gui` are not included in the test above. You can run test below to test module `url` and/or `gui` individually:

``` sh
$ ./dinfio ../tests/module_url.fio
```
``` sh
$ ./dinfio ../tests/module_gui.fio
```

## Notes

- Module `url` and `gui` are not included in compilation process by default. You can activate them by changing the config in file `compile_linux.sh`, `compile_linux_armv7.sh`, `compile_linux_docker.sh`, `compile_macos.sh`, or `compile_windows.bat`, depending on your platform
- If you want to compile module `url` and your [libcurl](https://curl.se/libcurl/) version is greater than or equal to 7.56, then add macro definition `#define __NEW_CURL__` to file [`src/modules/url/url.cpp`](src/modules/url/url.cpp)
- Module `gui` is not available on Linux Docker
- Module `url` is required by [Dima](src/dima/), so you have to activate it if you want to build Dima

## Notes for Windows

- If you want to compile module `url`, then open file [`compile_windows.bat`](compile_windows.bat), and change `LIBCURL_PATH` with your `libcurl` path. For example:

    ``` bat
    set LIBCURL_PATH=C:\libcurl
    ```
- As well as if you want to compile module `gui`, then open file [`compile_windows.bat`](compile_windows.bat), and change `WXWIDGETS_PATH` with your `wxwidgets` path. For example:

    ``` bat
    set WXWIDGETS_PATH=C:\wxwidgets
    ```

## Required Build Tools and Libraries

- [g++](https://gcc.gnu.org/) >= 5.4.0 &mdash; If you are going to compile Dinfio on Linux
- [Clang](https://clang.llvm.org/) >= 9.0.0 &mdash; If you are going to compile Dinfio on macOS
- [MinGW with g++](https://sourceforge.net/projects/mingw/) >= 9.2.0 &mdash; If you are going to compile Dinfio on Windows. MSVC is not tested yet
- [libcurl](https://curl.se/libcurl/) >= 7.47 &mdash; If you want to compile `url` module
- [wxWidgets](https://www.wxwidgets.org/) >= 3.1.4 (>= 3.0.4 on Raspberry Pi OS) &mdash; If you want to compile `gui` module
