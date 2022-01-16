# Building Dinfio

Before building Dinfio, please make sure you have all the [required build tools and libraries](#required-build-tools-and-libraries) installed. Then, download the source code by cloning the git repository:
```
$ git clone https://github.com/dinfio/dinfio.git
```

After the source code downloaded, go to directory `dinfio`:
```
$ cd dinfio
```
<br>

Open file [`src/header.h`](src/header.h), and point to  `__DINFIO_PATH__` constant (at line 44 or 51 or 58, depending on your platform):

``` cpp
const string __DINFIO_PATH__ = "/usr/local/dinfio/";
```

Change the constant value with your build path (absolute path), for example:

``` cpp
const string __DINFIO_PATH__ = "/home/faruq/Documents/dinfio/build/linux/";
```
<br>

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
<br>

Once it is compiled, go to your build path (for example: `cd build/linux`), and run Dinfio executable:

```
$ ./dinfio -v
```

If you see the Dinfio version, then Dinfio is successfully compiled.
<br>

## Notes

- Module `gui` and `url` are not included in compilation process by default. You can activate it by changing the config in file `compile_linux.sh`, `compile_linux_armv7.sh`, `compile_linux_docker.sh`, `compile_macos.sh`, or `compile_windows.bat`, depending on your platform
- If you want to compile module `url` and your [libcurl](https://curl.se/libcurl/) version is greater than or equal to 7.56, then add macro definition `#define __NEW_CURL__` to file [`src/modules/url/url.cpp`](src/modules/url/url.cpp)
- Module `gui` is not available on Linux Docker

## Required Build Tools and Libraries

- [g++](https://gcc.gnu.org/) >= 5.4.0 &mdash; If you compile Dinfio on Linux
- [Clang](https://clang.llvm.org/) >= 9.0.0 &mdash; If you compile Dinfio on macOS
- [MinGW with g++](https://sourceforge.net/projects/mingw/) >= 9.2.0 &mdash; If you compile Dinfio on Windows. MSVC is not tested yet
- [libcurl](https://curl.se/libcurl/) >= 7.47 &mdash; If you want to compile `url` module
- [wxWidgets](https://www.wxwidgets.org/) >= 3.1.4 (>= 3.0.4 on Raspberry Pi OS) &mdash; If you want to compile `gui` module
