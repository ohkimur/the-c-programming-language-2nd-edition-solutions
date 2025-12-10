rwildcard=$(foreach d, $(wildcard $(1:=/*)), $(call rwildcard, $d, $2) $(filter $(subst *, %, $2), $d))

SOURCES = $(call rwildcard, ., *.c, *.h)
DEBUG_FILES = $(call rwildcard, ., *.dSYM)
EXECS = $(SOURCES:%.c=%)
LDLIBS = -lm
CFLAGS = -Wall -Wextra -Wpedantic

# Find clang tools: check PATH first, then Homebrew LLVM location
LLVM_PREFIX := $(shell brew --prefix llvm 2>/dev/null)
CLANG_FORMAT := $(or $(shell command -v clang-format 2>/dev/null),$(wildcard $(LLVM_PREFIX)/bin/clang-format))
CLANG_TIDY := $(or $(shell command -v clang-tidy 2>/dev/null),$(wildcard $(LLVM_PREFIX)/bin/clang-tidy))

all: install-hooks $(EXECS)

lint:
	@echo "Linting with compiler warnings..."
	@for f in $(filter %.c, $(SOURCES)); do \
		$(CC) $(CFLAGS) -fsyntax-only $$f 2>&1 || exit 1; \
	done
ifneq ($(CLANG_TIDY),)
	@echo "Running clang-tidy..."
	@for f in $(filter %.c, $(SOURCES)); do \
		$(CLANG_TIDY) $$f -- $(CFLAGS) 2>&1 || exit 1; \
	done
else
	@echo "Skipping clang-tidy (not installed). Install with: brew install llvm"
endif
	@echo "Lint passed!"

format:
ifeq ($(CLANG_FORMAT),)
	$(error clang-format not found. Install with: brew install llvm)
endif
	find . \( -name '*.c' -o -name '*.h' \) -print0 | xargs -0 $(CLANG_FORMAT) -i

format-check:
ifeq ($(CLANG_FORMAT),)
	$(error clang-format not found. Install with: brew install llvm)
endif
	find . \( -name '*.c' -o -name '*.h' \) -print0 | xargs -0 $(CLANG_FORMAT) --dry-run --Werror

check: format-check lint

install-hooks:
	@if [ -d .git ] && [ ! -f .git/hooks/pre-commit ]; then \
		cp scripts/pre-commit .git/hooks/pre-commit; \
		chmod +x .git/hooks/pre-commit; \
		echo "Pre-commit hook installed."; \
	fi

clean:
	@for f in $(EXECS) $(DEBUG_FILES); do \
		if [ -e "$$f" ] || [ -d "$$f" ]; then \
			rm -rf "$$f" && echo "Removed: $$f"; \
		fi; \
	done

.PHONY: all lint format format-check check install-hooks clean
