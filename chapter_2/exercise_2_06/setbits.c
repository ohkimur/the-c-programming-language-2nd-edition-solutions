#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)                                                   \
    (byte & 128 ? '1' : '0'), (byte & 64 ? '1' : '0'),                         \
        (byte & 32 ? '1' : '0'), (byte & 16 ? '1' : '0'),                      \
        (byte & 8 ? '1' : '0'), (byte & 4 ? '1' : '0'),                        \
        (byte & 2 ? '1' : '0'), (byte & 1 ? '1' : '0')

unsigned int setbits(int x, int p, int n, int y);

int main(void) {
    // Using hexadecimal instead of binary literals (0b...) for C89/C99
    // compatibility 0xFF = 0b11111111, 0x06 = 0b0110
    unsigned int x = 0xFF;
    unsigned int y = 0x06;

    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(x));
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(setbits(x, 2, 4, y)));

    return 0;
}

unsigned int setbits(int x, int p, int n, int y) {
    ++p; // First position is 0

    // Use ~0U (unsigned) instead of ~0 (signed) to avoid undefined behavior
    // when left-shifting. Left-shifting a negative signed value is undefined.
    unsigned int mask1 = (~(~(~0U << n) << p) & x);
    unsigned int mask2 = (~(~0U << n) & y) << p;

    return mask1 | mask2;
}

// NOTE: Masking is a very good technique to work with bits. We can think about
// logic AND as a multiply and for OR as an addition.
