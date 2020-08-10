# The C Programming Language 2nd Edition - Solutions

## Introduction
**The C Programming Language** is a very popular book and sometimes people refer to it as **K&R**. The authors *Brian W. Kernighan* and *Dennis M. Ritchie* have done a very good job of explaining the core concepts of programming. The focus of the book is the C programming language, however, the approach is general, so it can be extended to all programming languages.

Each chapter of the book contains **exercises** that could be very helpful to better understand the C language. The exercises are designed so that anybody can solve them with the knowledge acquired up to that exercise.

This repository contains the **solutions** to the exercises from each chapter of the book. These solutions are meant to be helpful for those who want to *learn* to program with the C language.

## Environment
The source code is not tight up to an IDE, so any text editor can be used. However, there are useful tasks and settings available for [Visual Studio Code](https://code.visualstudio.com/). For a **better experience** using this editor, the C/C++ extension can provide some very helpful features specific to the C programming language.

### Compilers
To be able to write programs in C, a compiler is required. There are many options available for each operating system.

#### macOS
The [**clang**](https://clang.llvm.org/get_started.html) compiler is a very nice choice when using macOS. It is available with **Xcode Command Line Tools**, which can be easily installed using the following command:

```shell
$ xcode-select --install
```

#### Linux
The [**gcc**](https://gcc.gnu.org/) compiler is a very popular way to build C programs and it is a good choice when using Linux. Each distro has its own set of **development tools** that comes with the gcc compiler out of the box. The development tools can be installed with the following commands:

##### Ubuntu / Debian / Debian derivatives
```shell
$ sudo apt-get update
$ sudo apt-get install build-essential
```

##### Arch Linux
```shell
$ sudo pacman -Sy base-devel
```

##### Fedora
```shell
$ sudo yum update
$ sudo yum groupinstall "Development Tools" "Legacy Software Development"
```

#### Windows

Because Windows is not a Unix like operating system, [**Windows Subsystem for Linux**](https://docs.microsoft.com/en-us/windows/wsl/)  (a.k.a. WSL) could be a very good approach when writing C programs. It provides a full Linux system that can make the programming experience much better. The official documentation has a pretty good explanation about how to [install WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

[**MinGW Compiler Collection**](http://www.mingw.org/) is another good alternative to have access to the gcc compiler on a Windows system. The official documentation shows how it can be [installed](http://www.mingw.org/wiki/Getting_Started) step by step.

## Debugers

I used the __gdb__ debuger, available through __Windows Subsystem for Linux__ (_WSL_) with the __Ubuntu 18.04__. This debugger is also available through __Xcode Command Line Tools__ on macOS.

For a __*simple* programming environment__ it was created a __build task__ and a __debug task__ in _VS Code_.
