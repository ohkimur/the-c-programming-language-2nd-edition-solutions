# Contributing

Thanks for your interest in contributing! This guide will help you get started.

## Quick Start

1. Fork and clone the repository
2. Create a new branch: `git checkout -b my-fix`
3. Make your changes
4. Build: `make` (this also installs git hooks automatically)
5. Commit and push (the git commit hook will check formatting and lint)
6. Open a pull request

## Requirements

You'll need:
- A C compiler (GCC or Clang)
- `make` for building
- `clang-format` and `clang-tidy` for code quality checks

### Installing Dependencies

**macOS:**
```shell
brew install llvm
```
> The Makefile automatically finds the tools from Homebrew's LLVM installation - no need to modify your PATH.

**Ubuntu / Debian:**
```shell
sudo apt-get install clang-format clang-tidy
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
| `make install-hooks` | Install git pre-commit hook (runs automatically) |
| `make clean` | Remove compiled files |

## Before Submitting

Git hooks are installed automatically when you run `make`, so formatting and linting checks will run before each commit.

You can also run checks manually:

```shell
make format   # Format your code
make check    # Run all checks
```

The CI will automatically check formatting and linting on your pull request.

## Code Style

We use `clang-format` with minimal configuration (LLVM style, 4-space indentation). Just run `make format` and your code will be properly formatted.

Additional rules enforced by `clang-tidy`:

### One variable per declaration

Declare each variable on its own line for better readability.

```c
// ✗ Avoid
int x, y, z;
float fahr, celsius;

// ✓ Preferred
int x;
int y;
int z;
float fahr;
float celsius;
```

## What to Contribute

- **Bug fixes** - Found an error in a solution? Please fix it!
- **Improvements** - Better algorithms, clearer code, or better comments
- **Missing solutions** - Some exercises may be missing solutions
- **Documentation** - Improve explanations or add helpful comments

## Questions?

Feel free to open an issue if you have questions or need help!
