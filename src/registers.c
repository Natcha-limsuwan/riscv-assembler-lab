#include <stdlib.h>

int parse_register(const char *name) {
    if (!name || name[0] != 'x') return -1;

    char *end;
    long v = strtol(name + 1, &end, 10);
    if (*end != '\0') return -1;
    return (v >= 0 && v <= 31) ? (int)v : -1;
}