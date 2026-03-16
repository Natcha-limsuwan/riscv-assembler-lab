#include <string.h>
#include "symbols.h"

#define MAX_SYMBOLS 256

static struct {
    char name[64];
    int addr;
} symbol_table[MAX_SYMBOLS];
static int symbol_count = 0;

void symbols_reset(void) {
    symbol_count = 0;
}

int symbols_add(const char *label, int addr) {
    if (!label || !label[0]) return -1;
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, label) == 0) return -1;
    }
    if (symbol_count >= MAX_SYMBOLS) return -1;
    strncpy(symbol_table[symbol_count].name, label, sizeof(symbol_table[symbol_count].name)-1);
    symbol_table[symbol_count].name[sizeof(symbol_table[symbol_count].name)-1] = '\0';
    symbol_table[symbol_count].addr = addr;
    symbol_count++;
    return 0;
}

int symbols_find(const char *label) {
    if (!label) return -1;
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, label) == 0) return symbol_table[i].addr;
    }
    return -1;
}
