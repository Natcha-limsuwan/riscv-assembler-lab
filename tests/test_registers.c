#include <stdio.h>
#include <stdlib.h>
#include "../src/registers.h"

static void expect(int got, int want, const char *input) {
    if (got != want) {
        fprintf(stderr, "FAIL: %s => got %d, want %d\n", input, got, want);
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    expect(parse_register("x0"), 0, "x0");
    expect(parse_register("x1"), 1, "x1");
    expect(parse_register("x5"), 5, "x5");
    expect(parse_register("x31"), 31, "x31");

    expect(parse_register("x32"), -1, "x32");
    expect(parse_register("x-1"), -1, "x-1");
    expect(parse_register("y5"), -1, "y5");
    expect(parse_register(""), -1, "");
    expect(parse_register(NULL), -1, "NULL");

    printf("PASS: test_registers\n");
    return EXIT_SUCCESS;
}
