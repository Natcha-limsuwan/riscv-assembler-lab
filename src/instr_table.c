#include <string.h>
#include "instr_table.h"

static instr_desc instr_table[] = {
    {"add", FMT_R, 0x33, 0x0, 0x00},
    {"sub", FMT_R, 0x33, 0x0, 0x20},
    {"addi", FMT_I, 0x13, 0x0, 0x00},
    {"lw", FMT_I, 0x03, 0x2, 0x00},
    {"sw", FMT_S, 0x23, 0x2, 0x00},
    {"beq", FMT_B, 0x63, 0x0, 0x00},
    {"jal", FMT_J, 0x6F, 0x0, 0x00},
    {NULL, 0, 0, 0, 0}
};

void instr_table_init(void) { (void)instr_table; }

const instr_desc *instr_table_find(const char *mnemonic) {
    if (!mnemonic) return NULL;
    for (int i = 0; instr_table[i].name; i++) {
        if (strcmp(instr_table[i].name, mnemonic) == 0) {
            return &instr_table[i];
        }
    }
    return NULL;
}
