# Building Dinfio

Before building Dinfio, please make sure you have all the [required build tools and libraries](#required-build-tools-and-libraries) installed. Then, download the source code by cloning the git repository:
```
$ git clone https://github.com/dinfio/dinfio.git
```

After the source code downloaded, go to directory `dinfio`:
```
$ cd dinfio
```

Open file [`src/header.h`](src/header.h), and point to  `__DINFIO_PATH__` constant (at line 44 or 51 or 58, depending on your platform):

``` cpp
const string __DINFIO_PATH__ = "/usr/local/dinfio/";
```

Change the constant value with your build path, for example:

``` cpp
const string __DINFIO_PATH__ = "/home/faruq/Documents/dinfio/build/linux/";
```

And compile:

- On Linux x86_64:
```
$ ./compile_linux.sh
```

- On Linux ARMv7:
```
$ ./compile_linux_armv7.sh
```

- On Linux Docker:
```
$ ./compile_linux_docker.sh
```

- On macOS:
```
$ ./compile_macos.sh
```

- On Windows:
```
> compile_windows.bat
```

## Required Build Tools and Libraries

- [g++](https://gcc.gnu.org/) >= 5.4 &mdash; If you compile Dinfio on Linux
- [Clang](https://clang.llvm.org/) >= 9.0.0 &mdash; If you compile Dinfio on macOS
- [MinGW with g++](https://sourceforge.net/projects/mingw/) >= 9.2.0 &mdash; If you compile Dinfio on Windows. MSVC is not tested yet
- [libcurl](https://curl.se/libcurl/) >= 7.47
- [wxWidgets](https://www.wxwidgets.org/) >= 3.1.4 &mdash; If you want to use GUI module
