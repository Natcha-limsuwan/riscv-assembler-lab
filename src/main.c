#include <stdio.h>
#include "assembler.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.s> <output.hex>\n", argv[0]);
        return 1;
    }
    return assemble_file(argv[1], argv[2]) == 0 ? 0 : 1;
}
