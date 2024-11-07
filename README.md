# findex

## Table of Contents
- [Introduction](#introduction)
- [Documentation](#documentation)
- [Supported Compilers](#supported-compilers)
- [Requirements](#requirements)
- [Build](#build)
- [Install](#install)

## Introduction

Search for files that match specified criteria.

## Documentation

In order to learn how to use **findex**, feel free to check 
the [documentation](docs/index.md).

If you want to generate Doxygen documentation, you can use the `doxygen Doxyfile` command, and 
the results will be placed in the `docs` directory.

## Supported Compilers

The following compilers are currently known to be compatible:

| Compiler             | Standard Library | Test Environment   |
| :------------------- | :--------------- | :----------------- |
| GCC >= 11.4.0        | libstdc++        | Ubuntu 22.04       |
| MSVC >= 19.41.34123  | Microsoft STL    | Visual Studio 2022 |

## Requirements

To compile this software, you must have the following tools and libraries installed:
- [CMake 3.22](https://www.cmake.org/)
- [speed](https://github.com/killianvalverde/speed/tree/develop)

## Build

Use the folowing commands to buil and install the CMake project:

1. Create a directory to hold the build output and generate the native build scripts:

       cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release

2. Compile the project directly from CMake using the native build scripts:

       cmake --build cmake-build-release --config Release

## Install

By default, CMake installs the software in a standard location. If you wish to customize the 
installation directory, use the `--prefix <path>` option at the end of the CMake command to specify 
the desired path. Note that depending on your system, elevated privileges may be required to 
complete the installation. The provided commands take this into account.

### Linux

Run the following Bash command to install the software with root privileges:

    sudo cmake --install cmake-build-release --config Release

### Windows

Run the following PowerShell command to install the software with administrator privileges:

    Start-Process powershell -Verb RunAs -ArgumentList "-Command", `
        "Set-Location -Path '$PWD'; cmake --install cmake-build-release --config Release"
