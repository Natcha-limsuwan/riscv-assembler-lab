#ifndef INSTR_TABLE_H
#define INSTR_TABLE_H

typedef enum { FMT_R, FMT_I, FMT_S, FMT_B, FMT_J } instr_format_t;

typedef struct {
    const char *name;
    instr_format_t fmt;
    unsigned opcode;
    unsigned funct3;
    unsigned funct7;
} instr_desc;

void instr_table_init(void);
const instr_desc *instr_table_find(const char *mnemonic);

#endif // INSTR_TABLE_H
