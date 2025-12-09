rwildcard=$(foreach d, $(wildcard $(1:=/*)), $(call rwildcard, $d, $2) $(filter $(subst *, %, $2), $d))

SOURCES = $(call rwildcard, ., *.c, *.h)
DEBUG_FILES = $(call rwildcard, ., *.dSYM)
EXECS = $(SOURCES:%.c=%)
LDLIBS = -lm
CFLAGS = -Wall -Wextra -Wpedantic

all: $(EXECS)

lint:
	@echo "Linting with compiler warnings..."
	@for f in $(filter %.c, $(SOURCES)); do \
		$(CC) $(CFLAGS) -fsyntax-only $$f 2>&1 || exit 1; \
	done
	@echo "Lint passed!"

format:
	find . \( -name '*.c' -o -name '*.h' \) -print0 | xargs -0 clang-format -i

format-check:
	find . \( -name '*.c' -o -name '*.h' \) -print0 | xargs -0 clang-format --dry-run --Werror

check: format-check lint

clean:
	@for f in $(EXECS) $(DEBUG_FILES); do \
		if [ -e "$$f" ] || [ -d "$$f" ]; then \
			rm -rf "$$f" && echo "Removed: $$f"; \
		fi; \
	done

.PHONY: all lint format format-check check clean
