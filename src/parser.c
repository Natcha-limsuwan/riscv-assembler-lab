#include <ctype.h>
#include <string.h>
#include "parser.h"

static char *trim(char *s) {
    char *p = s;
    while (*p && isspace((unsigned char)*p)) p++;
    if (*p == '\0') return p;
    char *end = p + strlen(p) - 1;
    while (end > p && isspace((unsigned char)*end)) *end-- = '\0';
    if (p != s) memmove(s, p, strlen(p) + 1);
    return s;
}

int parse_line(const char *line, char *label, char *mnemonic, char *operands) {
    if (!line || !label || !mnemonic || !operands) return -1;

    char buf[512];
    strncpy(buf, line, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    char *p = buf;
    char *comment = strchr(p, '#');
    if (comment) *comment = '\0';

    p = trim(p);
    if (*p == '\0') {
        label[0] = '\0';
        mnemonic[0] = '\0';
        operands[0] = '\0';
        return 0;
    }

    char *colon = strchr(p, ':');
    if (colon) {
        *colon = '\0';
        char *lbl = trim(p);
        strncpy(label, lbl, 63);
        label[63] = '\0';
        p = colon + 1;
    } else {
        label[0] = '\0';
    }

    p = trim(p);
    if (*p == '\0') {
        mnemonic[0] = '\0';
        operands[0] = '\0';
        return 0;
    }

    char *token = strtok(p, " \t\r\n");
    if (!token) {
        mnemonic[0] = '\0';
        operands[0] = '\0';
        return -1;
    }

    strncpy(mnemonic, token, 31);
    mnemonic[31] = '\0';

    char *rest = strtok(NULL, "");
    if (rest) {
        char *trimmed = trim(rest);
        strncpy(operands, trimmed, 255);
        operands[255] = '\0';
    } else {
        operands[0] = '\0';
    }

    return 1;
}
