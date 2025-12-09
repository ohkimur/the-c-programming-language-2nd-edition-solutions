#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)                                                   \
    (byte & 128 ? '1' : '0'), (byte & 64 ? '1' : '0'),                         \
        (byte & 32 ? '1' : '0'), (byte & 16 ? '1' : '0'),                      \
        (byte & 8 ? '1' : '0'), (byte & 4 ? '1' : '0'),                        \
        (byte & 2 ? '1' : '0'), (byte & 1 ? '1' : '0')

unsigned int invert(int x, int p, int n);

int main(void) {
    // Using hexadecimal instead of binary literals (0b...) for C89/C99
    // compatibility 0xD7 = 0b11010111
    unsigned int x = 0xD7;

    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(x));
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(invert(x, 1, 4)));

    return 0;
}

unsigned int invert(int x, int p, int n) {
    ++p; // First position is 0

    // Use ~0U (unsigned) instead of ~0 (signed) to avoid undefined behavior
    // when left-shifting. Left-shifting a negative signed value is undefined.
    unsigned int mask1 = ~(~0U << n) << p;
    unsigned int mask2 = ~mask1 & x;

    return mask2 | ~x;
}
