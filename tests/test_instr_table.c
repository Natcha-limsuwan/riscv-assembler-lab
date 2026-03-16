#include <stdio.h>
#include <stdlib.h>
#include "../src/instr_table.h"

int main(void) {
    instr_table_init();
    const instr_desc *i = instr_table_find("add");
    if (!i || i->fmt != FMT_R || i->opcode != 0x33) {
        fprintf(stderr, "FAIL add\n");
        return 1;
    }
    i = instr_table_find("nope");
    if (i != NULL) {
        fprintf(stderr, "FAIL unknown\n");
        return 1;
    }
    printf("PASS test_instr_table\n");
    return 0;
}
