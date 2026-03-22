# ff

## Table of Contents
- [Introduction](#introduction)
- [Documentation](#documentation)
- [Supported Compilers](#supported-compilers)
- [Requirements](#requirements)
- [Build](#build)
- [Install](#install)

## Introduction

__ff__ is a high-performance single-core file searcher that is up to 2× faster than __POSIX__ 
`find` and __PowerShell__ `Get-ChildItem` in most scenarios.

## Documentation

To access the help menu of this software in order to know all the available options and commands, 
simply run `ff --help` in a terminal after installing it.

If you want to generate __Doxygen__ documentation, you can use the `doxygen Doxyfile` command, and 
the results will be placed in the `./docs` directory.

## Supported Compilers

The following compilers are currently known to be compatible:

| Compiler                                                   | Standard Library | Test Environment   |
|:-----------------------------------------------------------|:-----------------|:-------------------|
| [GCC](https://gcc.gnu.org/) >= 13.3.0                      | libstdc++        | Ubuntu 24.04       |
| [MSVC](https://visualstudio.microsoft.com/) >= 19.50.35720 | Microsoft STL    | Visual Studio 2026 |

## Requirements

To compile this software, you must have the following tools and libraries installed:

| Software                                | Type                   | Platform Dependency | GNU/Linux Installation Command |
|:----------------------------------------|:-----------------------|:--------------------|:-------------------------------|
| [CMake](https://www.cmake.org/) >= 3.28 | Build system generator | All                 | `sudo apt install cmake`       |

## Build

Follow these steps to build the project:

1. __Clone__ the repository and enter the project directory:

       git clone --recursive https://github.com/killianvalverde/ff.git && cd ff

2. Generate the build system using __CMake__:

       cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release

3. __Compile__ the project:

       cmake --build cmake-build-release --config Release

## Install

By default, __CMake__ installs the software in a standard location. If you wish to customize the 
installation directory, use the `--prefix <path>` option at the end of the __CMake__ command to 
specify the desired path. Note that depending on your system, elevated privileges may be required 
to complete the installation. The provided commands take this into account.

### Linux

Run the following __Bash__ command to install the software with root privileges:

    sudo cmake --install cmake-build-release --config Release

### Windows

Run the following __PowerShell__ command to install the software with administrator privileges:

    Start-Process powershell -Verb RunAs -ArgumentList "-Command", `
        "Set-Location -Path '$PWD'; cmake --install cmake-build-release --config Release; pause"
