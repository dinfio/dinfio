# Dima: Dinfio Module Manager

Dima is a module manager for Dinfio. You can install and uninstall modules using Dima.

## Building Dima

Please follow these steps to build Dima:

- Compile the Dima Launcher, please see [`launcher/README.md`](launcher/README.md) for more information
- Copy file `main.fio` and directory `helpers` to `../../build/<platform>/dima`

## Note

- Module `url` is required by Dima, so you have to activate module `url` in Dinfio compilation process. Please see [`../../BUILD.md`](../../BUILD.md#notes) for more information about how to activate it