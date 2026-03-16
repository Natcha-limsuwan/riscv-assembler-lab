#include <stdio.h>
#include <stdint.h>
#include "../src/encode.h"

int main(void) {
    if (encode_r(0x00, 2, 1, 0x0, 3, 0x33) != 0x002081b3u) return 1;
    if (encode_i(5, 1, 0x0, 3, 0x13) != 0x00508193u) return 1;
    if (encode_s(4, 2, 1, 0x2, 0x23) != 0x0020a223u) return 1;
    if (encode_b(8, 2, 1, 0x0, 0x63) != 0x00208463u) return 1;
    if (encode_j(4, 0, 0x6f) != 0x40006fu) return 1;
    printf("PASS test_encode\n");
    return 0;
}
