#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/parser.h"

static void expect_parse(const char *line, const char *label, const char *mnemonic, const char *operands) {
    char got_label[64], got_mnemonic[64], got_operands[256];
    int rc = parse_line(line, got_label, got_mnemonic, got_operands);
    if (rc < 0 || strcmp(got_label, label) != 0 || strcmp(got_mnemonic, mnemonic) != 0 || strcmp(got_operands, operands) != 0) {
        fprintf(stderr, "FAIL parse_line '%s' => got '%s' '%s' '%s', expected '%s' '%s' '%s'\n", line, got_label, got_mnemonic, got_operands, label, mnemonic, operands);
        exit(1);
    }
}

int main(void) {
    expect_parse("", "", "", "");
    expect_parse("# comment", "", "", "");
    expect_parse("label: add x1, x2, x3", "label", "add", "x1, x2, x3");
    expect_parse("  addi x4, x5, 10  ", "", "addi", "x4, x5, 10");
    printf("PASS test_parser\n");
    return 0;
}
