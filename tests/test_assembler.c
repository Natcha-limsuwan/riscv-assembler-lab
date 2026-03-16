#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/assembler.h"

int main(void) {
    const char *infile = "tests/temp_test.s";
    const char *outfile = "tests/temp_test.hex";
    FILE *f = fopen(infile, "w");
    if (!f) return 1;
    fprintf(f, "addi x1, x0, 5\n");
    fprintf(f, "add x2, x1, x1\n");
    fprintf(f, "beq x1, x2, end\n");
    fprintf(f, "jal x0, end\n");
    fprintf(f, "end: add x3, x0, x0\n");
    fclose(f);
    if (assemble_file(infile, outfile) != 0) return 1;
    f = fopen(outfile, "r");
    if (!f) return 1;
    char line[128];
    if (!fgets(line, sizeof(line), f)) return 1;
    if (strncmp(line, "00500093", 8) != 0) return 1;
    if (!fgets(line, sizeof(line), f)) return 1;
    if (strncmp(line, "00108133", 8) != 0) return 1;
    if (!fgets(line, sizeof(line), f)) return 1;
    if (strncmp(line, "00208463", 8) != 0) return 1;
    if (!fgets(line, sizeof(line), f)) return 1;
    if (strncmp(line, "0040006f", 8) != 0) return 1;
    if (!fgets(line, sizeof(line), f)) return 1;
    if (strncmp(line, "000001b3", 8) != 0) return 1;
    fclose(f);
    remove(infile);
    remove(outfile);
    printf("PASS test_assembler\n");
    return 0;
}
