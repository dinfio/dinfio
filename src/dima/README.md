# Dima: Dinfio Module Manager

Dima is a module manager for Dinfio. You can install and uninstall modules using Dima.

## Building Dima

Please follow these steps to build Dima:

- Configure and compile the [Dima Launcher](launcher/README.md):
    - Open file [`launcher/main.cpp`](launcher/main.cpp), and point to  `__DINFIO_PATH__` constant (at line 21 or 23 or 25, depending on your platform):

        ``` cpp
        const string __DINFIO_PATH__ = "/usr/local/dinfio/";
        ```

    - Change the constant value with your Dinfio build path (absolute path), for example:

        ``` cpp
        const string __DINFIO_PATH__ = "/home/sweet/Documents/dinfio/build/";
        ```

    - And compile:
        - On Linux x86_64, ARMv7, ARM64, Docker:
            ``` sh
            $ ./compile_linux.sh
            ```

        - On macOS:
            ``` sh
            $ ./compile_macos.sh
            ```

        - On Windows:
            ```
            > compile_windows.bat
            ```

- Test the Dima:
    ``` sh
    $ cd ../../build/dima/
    $ ./dima list
    ```

## Note

- Module `url` is required by Dima, so you have to activate module `url` in Dinfio compilation process. Please see [../../BUILDING.md](../../BUILDING.md#notes) for more information about how to activate it
