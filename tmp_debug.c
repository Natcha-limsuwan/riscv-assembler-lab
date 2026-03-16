#include <stdio.h>
#include "parser.h"
#include "instr_table.h"
#include "registers.h"
#include "symbols.h"
#include "encode.h"

int main(void) {
    char label[64], mnemonic[64], operands[256];
    int r = parse_line("addi x1, x0, 5", label, mnemonic, operands);
    printf("parse_line r=%d label=%s mnemonic=%s operands=%s\n", r, label, mnemonic, operands);
    const instr_desc *d = instr_table_find(mnemonic);
    printf("instr desc %p name=%s fmt=%d\n", d, d ? d->name : NULL, d ? d->fmt : -1);
    printf("parse_register x1=%d\n", parse_register("x1"));
    unsigned val = encode_i(5, 1, 0, 3, 0x13);
    printf("val=0x%08x\n", val);
    return 0;
}
