# The C Programming Language 2nd Edition - Solutions

![C/C++ CI](https://github.com/gleesik/the-c-programming-language-2nd-edition-solutions/workflows/C/C++%20CI/badge.svg)

Solutions to exercises from **The C Programming Language** (2nd Edition) by Brian W. Kernighan and Dennis M. Ritchie, commonly known as **K&R**.

## Getting Started

### Prerequisites

You need a C compiler:

**macOS:**
```shell
xcode-select --install
```

**Ubuntu / Debian:**
```shell
sudo apt-get update && sudo apt-get install build-essential
```

**Windows:**
Use [WSL](https://docs.microsoft.com/en-us/windows/wsl/install) (recommended) or [MinGW](http://www.mingw.org).

### Building

Build all exercises:
```shell
make
```

Build a specific exercise:
```shell
cd chapter_1/exercise_1_01
make hello_world
./hello_world
```

Clean up:
```shell
make clean
```

## Repository Structure

```
chapter_N/
  exercise_N_XX/
    solution.c      # Solution source code
    file_in.txt     # Input file (if needed)
    file_out.txt    # Output file (if needed)
```

## Contributing

Contributions are welcome! See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

Quick start:
```shell
make format   # Format your code
make check    # Run all checks before submitting
```

## About the Book

**The C Programming Language** is a classic programming book. The exercises are designed so that you can solve them with the knowledge acquired up to that point in the book.

These solutions are meant to help those learning C. If you're working through the book, try solving the exercises yourself first!

## Tools

- **Editor:** Any text editor works. [VS Code](https://code.visualstudio.com) with the [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) is recommended.
- **Debugger:** [LLDB](https://lldb.llvm.org) (macOS) or [GDB](https://www.gnu.org/software/gdb) (Linux)
- **Formatter:** [clang-format](https://clang.llvm.org/docs/ClangFormat.html)

## License

This project is open source. Feel free to use these solutions for learning!
