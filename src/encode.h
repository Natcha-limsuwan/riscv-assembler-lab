#ifndef ENCODE_H
#define ENCODE_H

#include <stdint.h>

uint32_t encode_r(uint32_t funct7, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode);
uint32_t encode_i(int32_t imm, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode);
uint32_t encode_s(int32_t imm, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t opcode);
uint32_t encode_b(int32_t imm, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t opcode);
uint32_t encode_j(int32_t imm, uint32_t rd, uint32_t opcode);

#endif // ENCODE_H
