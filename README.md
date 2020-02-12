# The C Programming Language 2nd Edition - Solutions

## Introduction
Here are my solutions to the exercises in the book "The C Programming Language" (2nd edition) by Brian W. Kernighan and Dennis M. Ritchie. This is a very popular book and it's also referred to as K&R. I _tried_ to use the _best practices_ with the knowledge learned up to each exercise.

The book shows a lot of useful information about the C programming language, but more than that it gives a very good grasp on what programming really means.

## Environment
For the programming environment the __Visual Studio Code__ text editor was used. On top of this the __C/C++ extension__ was added to have acces to many __useful features__ specific for the C programming language. Also for simplicity the __Code Runner__ extension was used. Were created _specific configurations_ for the environment to accommodate the c programming language needs. 

## Compilers

For the first 5 chapters was used the __gcc__ compiler from MinGW compiler collection. A contraction of _"Minimalist GNU for Windows"_. It is a minimalist development environment for native Microsoft Windows applications.

Also I used the __gcc__ compiler available through __Windows Subsystem for Linux__ (_WSL_) with the __Ubuntu 18.04__ distribution installed. This compiler has some small advantages, over the __*MinGW*__ version, because the __linux environment__ it's _Unix_ based and this makes the development process of C programs more easy to work with.

Later I used the __clang__ compiler available through __Xcode Command Line Tools__ on the macOS. This evironment it's also _Unix_ based and has many advantages regarding C programming.

## Debugers

I used the __gdb__ debuger, available through __Windows Subsystem for Linux__ (_WSL_) with the __Ubuntu 18.04__. This debugger is also available through __Xcode Command Line Tools__ on macOS.

For a __*simple* programming environment__ it was created a __build task__ and a __debug task__ in _VS Code_.
