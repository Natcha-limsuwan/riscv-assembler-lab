CC=gcc
CFLAGS=-Wall -Wextra -Isrc

SRC=src/main.c src/assembler.c src/parser.c src/registers.c src/instr_table.c src/symbols.c src/encode.c

test_registers:
	$(CC) $(CFLAGS) tests/test_registers.c src/registers.c -o test_registers

test_parser:
	$(CC) $(CFLAGS) tests/test_parser.c src/parser.c -o test_parser

test_instr_table:
	$(CC) $(CFLAGS) tests/test_instr_table.c src/instr_table.c -o test_instr_table

test_symbols:
	$(CC) $(CFLAGS) tests/test_symbols.c src/symbols.c -o test_symbols

test_encode:
	$(CC) $(CFLAGS) tests/test_encode.c src/encode.c -o test_encode

test_assembler:
	$(CC) $(CFLAGS) tests/test_assembler.c src/assembler.c src/parser.c src/registers.c src/instr_table.c src/symbols.c src/encode.c -o test_assembler

assembler: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o assembler

clean:
	rm -f test_registers test_parser test_instr_table test_symbols test_encode test_assembler assembler tests/temp_test.s tests/temp_test.hex

.PHONY: test_registers test_parser test_instr_table test_symbols test_encode test_assembler assembler clean
