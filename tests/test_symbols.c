#include <stdio.h>
#include <stdlib.h>
#include "../src/symbols.h"

int main(void) {
    symbols_reset();
    if (symbols_add("foo", 0) != 0) return 1;
    if (symbols_add("foo", 4) != -1) return 1;
    if (symbols_find("foo") != 0) return 1;
    if (symbols_find("bar") != -1) return 1;
    printf("PASS test_symbols\n");
    return 0;
}
