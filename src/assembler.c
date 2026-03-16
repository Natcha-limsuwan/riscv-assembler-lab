#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"
#include "parser.h"
#include "instr_table.h"
#include "symbols.h"
#include "registers.h"
#include "encode.h"

static int parse_imm(const char *s, int *imm) {
    if (!s || !imm) return -1;
    char *end;
    long val = strtol(s, &end, 0);
    if (end == s || *end != '\0') return -1;
    *imm = (int)val;
    return 0;
}

static int parse_memory_op(const char *mem, int *imm, int *reg) {
    if (!mem || !imm || !reg) return -1;
    char buf[128];
    strncpy(buf, mem, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    char *open = strchr(buf, '(');
    char *close = strchr(buf, ')');
    if (!open || !close || open > close) return -1;
    *open = '\0';
    *close = '\0';
    int i;
    if (parse_imm(buf, &i) != 0) return -1;
    int r = parse_register(open + 1);
    if (r < 0) return -1;
    *imm = i;
    *reg = r;
    return 0;
}

static char *trim_whitespace(char *s) {
    if (!s) return NULL;
    while (*s && isspace((unsigned char)*s)) s++;
    if (*s == '\0') return s;
    char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
    return s;
}

int assemble_file(const char *input, const char *output) {
    if (!input || !output) return -1;
    FILE *fin = fopen(input, "r");
    if (!fin) return -1;
    symbols_reset();
    instr_table_init();
    char line[512];
    int pc = 0;
    int line_no = 0;
    while (fgets(line, sizeof(line), fin)) {
        line_no++;
        char label[64], mnemonic[64], operands[256];
        int pr = parse_line(line, label, mnemonic, operands);
        if (pr < 0) {
            fprintf(stderr, "assemble_file: parse_line error at line %d\n", line_no);
            fclose(fin);
            return -1;
        }
        if (label[0] != '\0') {
            if (symbols_add(label, pc * 4) != 0) {
                fprintf(stderr, "assemble_file: symbols_add error at line %d label=%s\n", line_no, label);
                fclose(fin);
                return -1;
            }
        }
        if (mnemonic[0] != '\0') pc++;
    }
    rewind(fin);
    FILE *fout = fopen(output, "w");
    if (!fout) { fclose(fin); return -1; }
    pc = 0;
    line_no = 0;
    while (fgets(line, sizeof(line), fin)) {
        line_no++;
        char label[64], mnemonic[64], operands[256];
        int pr = parse_line(line, label, mnemonic, operands);
        if (pr < 0) {
            fprintf(stderr, "assemble_file: parse_line error at line %d\n", line_no);
            fclose(fin);
            fclose(fout);
            return -1;
        }
        if (mnemonic[0] == '\0') continue;
        const instr_desc *desc = instr_table_find(mnemonic);
        if (!desc) {
            fprintf(stderr, "assemble_file: unknown mnemonic '%s' at line %d\n", mnemonic, line_no);
            fclose(fin);
            fclose(fout);
            return -1;
        }
        char opcopy[256];
        strncpy(opcopy, operands, sizeof(opcopy) - 1);
        opcopy[sizeof(opcopy) - 1] = '\0';
        char *ops[4] = {0};
        int opcount = 0;
        char *tok = strtok(opcopy, ",");
        while (tok && opcount < 4) {
            ops[opcount++] = trim_whitespace(tok);
            tok = strtok(NULL, ",");
        }
        uint32_t enc = 0;
        if (desc->fmt == FMT_R) {
            if (opcount != 3) { fclose(fin); fclose(fout); return -1; }
            int rd = parse_register(ops[0]);
            int rs1 = parse_register(ops[1]);
            int rs2 = parse_register(ops[2]);
            if (rd < 0 || rs1 < 0 || rs2 < 0) { fclose(fin); fclose(fout); return -1; }
            enc = encode_r(desc->funct7, rs2, rs1, desc->funct3, rd, desc->opcode);
        } else if (desc->fmt == FMT_I) {
            if (strcmp(desc->name, "lw") == 0) {
                if (opcount != 2) { fclose(fin); fclose(fout); return -1; }
                int rd = parse_register(ops[0]);
                int imm, rs1;
                if (rd < 0 || parse_memory_op(ops[1], &imm, &rs1) != 0) { fclose(fin); fclose(fout); return -1; }
                enc = encode_i(imm, rs1, desc->funct3, rd, desc->opcode);
            } else {
                if (opcount != 3) { fclose(fin); fclose(fout); return -1; }
                int rd = parse_register(ops[0]);
                int rs1 = parse_register(ops[1]);
                int imm;
                if (rd < 0 || rs1 < 0 || parse_imm(ops[2], &imm) != 0) { fclose(fin); fclose(fout); return -1; }
                enc = encode_i(imm, rs1, desc->funct3, rd, desc->opcode);
            }
        } else if (desc->fmt == FMT_S) {
            if (opcount != 2) { fclose(fin); fclose(fout); return -1; }
            int rs2 = parse_register(ops[0]);
            int imm, rs1;
            if (rs2 < 0 || parse_memory_op(ops[1], &imm, &rs1) != 0) { fclose(fin); fclose(fout); return -1; }
            enc = encode_s(imm, rs2, rs1, desc->funct3, desc->opcode);
        } else if (desc->fmt == FMT_B) {
            if (opcount != 3) { fclose(fin); fclose(fout); return -1; }
            int rs1 = parse_register(ops[0]);
            int rs2 = parse_register(ops[1]);
            int target = symbols_find(ops[2]);
            if (rs1 < 0 || rs2 < 0 || target < 0) { fclose(fin); fclose(fout); return -1; }
            int offset = target - pc * 4;
            enc = encode_b(offset, rs2, rs1, desc->funct3, desc->opcode);
        } else if (desc->fmt == FMT_J) {
            if (opcount != 2) { fclose(fin); fclose(fout); return -1; }
            int rd = parse_register(ops[0]);
            int target = symbols_find(ops[1]);
            if (rd < 0 || target < 0) { fclose(fin); fclose(fout); return -1; }
            int offset = target - pc * 4;
            enc = encode_j(offset, rd, desc->opcode);
        }
        fprintf(fout, "%08x\n", enc);
        pc++;
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
