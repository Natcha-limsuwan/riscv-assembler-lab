#include <stdint.h>
#include "encode.h"

uint32_t encode_r(uint32_t funct7, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode) {
    return (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
}

uint32_t encode_i(int32_t imm, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode) {
    uint32_t imm12 = (uint32_t)imm & 0xFFF;
    return (imm12 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
}

uint32_t encode_s(int32_t imm, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t opcode) {
    uint32_t imm12 = (uint32_t)imm & 0xFFF;
    uint32_t imm11_5 = (imm12 >> 5) & 0x7F;
    uint32_t imm4_0 = imm12 & 0x1F;
    return (imm11_5 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (imm4_0 << 7) | opcode;
}

uint32_t encode_b(int32_t imm, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t opcode) {
    uint32_t imm12 = (uint32_t)imm & 0xFFF;
    uint32_t imm11 = (imm12 >> 11) & 0x1;
    uint32_t imm4_1 = (imm12 >> 1) & 0xF;
    uint32_t imm10_5 = (imm12 >> 5) & 0x3F;
    uint32_t imm12h = (imm12 >> 12) & 0x1;
    return (imm12h << 31) | (imm10_5 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (imm4_1 << 8) | (imm11 << 7) | opcode;
}

uint32_t encode_j(int32_t imm, uint32_t rd, uint32_t opcode) {
    uint32_t imm20 = ((uint32_t)imm >> 1) & 0xFFFFF;
    uint32_t b20 = (imm20 >> 19) & 0x1;
    uint32_t b10_1 = imm20 & 0x3FF;
    uint32_t b11 = (imm20 >> 8) & 0x1;
    uint32_t b19_12 = (imm20 >> 10) & 0xFF;
    return (b20 << 31) | (b19_12 << 12) | (b11 << 20) | (b10_1 << 21) | (rd << 7) | opcode;
}
