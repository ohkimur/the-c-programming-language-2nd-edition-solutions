# Contributing

Thanks for your interest in contributing! This guide will help you get started.

## Quick Start

1. Fork and clone the repository
2. Create a new branch: `git checkout -b my-fix`
3. Make your changes
4. Format your code: `make format`
5. Test your changes: `make`
6. Commit and push
7. Open a pull request

## Requirements

You'll need:
- A C compiler (GCC or Clang)
- `clang-format` for code formatting
- `make` for building

### Installing clang-format

**macOS:**
```shell
brew install clang-format
```

**Ubuntu / Debian:**
```shell
sudo apt-get install clang-format
```

**Arch Linux:**
```shell
sudo pacman -S clang
```

**Fedora:**
```shell
sudo dnf install clang-tools-extra
```

## Available Commands

| Command | Description |
|---------|-------------|
| `make` | Build all exercises |
| `make format` | Format all code |
| `make format-check` | Check formatting (used by CI) |
| `make lint` | Run linter checks |
| `make check` | Run all checks (format + lint) |
| `make clean` | Remove compiled files |

## Before Submitting

Please run these commands before submitting a pull request:

```shell
make format   # Format your code
make check    # Run all checks
```

The CI will automatically check formatting and linting on your pull request.

## Code Style

We use `clang-format` with minimal configuration (LLVM style, 4-space indentation). Just run `make format` and your code will be properly formatted.

## What to Contribute

- **Bug fixes** - Found an error in a solution? Please fix it!
- **Improvements** - Better algorithms, clearer code, or better comments
- **Missing solutions** - Some exercises may be missing solutions
- **Documentation** - Improve explanations or add helpful comments

## Questions?

Feel free to open an issue if you have questions or need help!
