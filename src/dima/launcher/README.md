# Dima Launcher

This is a tiny C++ application to launch Dima main programme.
When you type `$ dima`, the application will launch `$ dinfio <dima_path>/main.fio`

## Configuring and Compiling

Open file [`main.cpp`](main.cpp), and point to  `__DINFIO_PATH__` constant (at line 21 or 23 or 25, depending on your platform):

``` cpp
const string __DINFIO_PATH__ = "/usr/local/dinfio/";
```

Change the constant value with your build path (absolute path), for example:

``` cpp
const string __DINFIO_PATH__ = "/home/sweet/Documents/dinfio/build/";
```

And compile:

- Linux x86_64:
```
$ ./compile_linux.sh
```

- Linux ARMv7:
```
$ ./compile_linux_armv7.sh
```

- Linux Docker:
```
$ ./compile_linux_docker.sh
```

- macOS:
```
$ ./compile_macos.sh
```

- Windows:
```
> compile_windows.bat
```