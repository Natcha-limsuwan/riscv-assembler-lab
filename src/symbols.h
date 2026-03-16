#ifndef SYMBOLS_H
#define SYMBOLS_H

int symbols_add(const char *label, int addr);
int symbols_find(const char *label);
void symbols_reset(void);

#endif // SYMBOLS_H
