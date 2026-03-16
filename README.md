# RISC-V Assembler Lab

Educational RISC-V assembler project in C. Implements a simplified subset of RV32I and a minimal assembler pipeline.

## Project structure

- `src/`
  - `main.c` - CLI entry point
  - `assembler.c` - two-pass assembler (label collection + encoding)
  - `parser.c` / `parser.h` - line parse utils
  - `registers.c` / `registers.h` - map register names `x0`..`x31`
  - `instr_table.c` / `instr_table.h` - instruction metadata table
  - `symbols.c` / `symbols.h` - symbol table for labels
  - `encode.c` / `encode.h` - R/I/S/B/J encoders

- `tests/`
  - `test_registers.c`
  - `test_parser.c`
  - `test_instr_table.c`
  - `test_symbols.c`
  - `test_encode.c`
  - `test_assembler.c`

## Build and run

### 1) Compile test modules

```sh
make test_registers
./test_registers

make test_parser
./test_parser

make test_instr_table
./test_instr_table

make test_symbols
./test_symbols

make test_encode
./test_encode

make test_assembler
./test_assembler
```

### 2) Build assembler binary

```sh
make assembler
./assembler <input.s> <output.hex>
```

### 3) Clean

```sh
make clean
```

## Supported instructions

- R: `add`, `sub`, `sll`, `slt`, `sltu`, `xor`, `srl`, `sra`, `or`, `and`
- I: `addi`, `slti`, `sltiu`, `xori`, `ori`, `andi`, `slli`, `srli`, `srai`, `lw`
- S: `sw`
- B: `beq`, `bne`, `blt`, `bge`, `bltu`, `bgeu`
- J: `jal`
- U not required in tests (not yet implemented)

## Pipeline

1. pass 1: read source lines, parse labels + instruction count, fill symbol table with address (pc*4)
2. pass 2: parse each instruction, lookup instruction descriptor, decode operands, compute branch/jump offset, encode bits, write 32-bit hex line

## Notes

- All tests currently pass.
- Assembler can emit output for simple programs.
- Instructions use immediate range and sign extension checks in the encoding modules.

## Example input

`examples/simple.s` (not included; create it manually):

```asm
addi x1, x0, 5
add x2, x1, x1
beq x1, x2, end
jal x0, end
end: add x3, x0, x0
```

## Example usage

```sh
./assembler examples/simple.s examples/simple.hex
cat examples/simple.hex
```

## Test coverage

- `registers`: x0..x31 parsing
- `parser`: label/mnemonic/operand splitting and comment removal
- `instr_table`: lookup for supported mnemonics
- `symbols`: add/find label symbol table
- `encode`: exact encoded bits for each ISA format
- `assembler`: full output equivalency for test sample

## Next step (optional)

- Add robust error messages, line numbers, out-of-range immediate check.
- Add more codegen test cases (20 / 50 / 120 lines) and compare with Venus simulator.
- Add `examples` folder and test report side-by-side.
