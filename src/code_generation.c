#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code_generation.h"
#include "symbol_table.h"
#include "utils.h"

#define MAX_OPERANDS 2

static const Instruction instruction_set[] = {
    {"mov", 0, 2}, {"cmp", 1, 2}, {"add", 2, 2}, {"sub", 3, 2},
    {"lea", 4, 2}, {"clr", 5, 1}, {"not", 6, 1}, {"inc", 7, 1},
    {"dec", 8, 1}, {"jmp", 9, 1}, {"bne", 10, 1}, {"red", 11, 1},
    {"prn", 12, 1}, {"jsr", 13, 1}, {"rts", 14, 0}, {"stop", 15, 0}
};

static int get_register_number(const char *reg);
static AddressingMode get_addressing_mode(const char *operand);
static bool encode_operand(const char *operand, int *value, bool *is_external);
static const Instruction* find_instruction(const char *operation);

bool generate_machine_code(const char *operation, const char *operands, MachineCode *code) {
    char op1[MAX_OPERAND_LENGTH] = {0}, op2[MAX_OPERAND_LENGTH] = {0};
    const Instruction *instr = find_instruction(operation);
    
    if (!instr) {
        fprintf(stderr, "Unknown operation: %s\n", operation);
        return false;
    }

    if (instr->operand_count > 0) {
        sscanf(operands, "%s %s", op1, op2);
    }

    // Encode first word
    code->first_word = (instr->opcode << 6);
    if (instr->operand_count > 0) {
        AddressingMode src_addr = get_addressing_mode(op1);
        AddressingMode dst_addr = get_addressing_mode(op2);
        code->first_word |= (src_addr << 4) | (dst_addr << 2);
    }
    code->first_word |= ARE_ABSOLUTE;

    // Encode operands
    code->second_word_exists = code->third_word_exists = code->is_external_reference = false;

    if (instr->operand_count > 0) {
        int value;
        bool is_external;

        if (encode_operand(op1, &value, &is_external)) {
            code->second_word = value;
            code->second_word_exists = true;
            if (is_external) {
                code->is_external_reference = true;
                strncpy(code->external_symbol, op1, MAX_SYMBOL_LENGTH);
            }
        }

        if (instr->operand_count > 1 && encode_operand(op2, &value, &is_external)) {
            code->third_word = value;
            code->third_word_exists = true;
            if (is_external) {
                code->is_external_reference = true;
                strncpy(code->external_symbol, op2, MAX_SYMBOL_LENGTH);
            }
        }
    }

    return true;
}

static int get_register_number(const char *reg) {
    if (reg[0] == 'r' && reg[1] >= '0' && reg[1] <= '7' && reg[2] == '\0') {
        return reg[1] - '0';
    }
    return -1;
}

static AddressingMode get_addressing_mode(const char *operand) {
    if (operand[0] == '#') return ADDRESSING_IMMEDIATE;
    if (operand[0] == '*') return ADDRESSING_REGISTER_INDIRECT;
    if (get_register_number(operand) != -1) return ADDRESSING_REGISTER_DIRECT;
    return ADDRESSING_DIRECT;
}

static bool encode_operand(const char *operand, int *value, bool *is_external) {
    int reg_num;
    *is_external = false;

    if (operand[0] == '#') {
        *value = atoi(operand + 1);
        return true;
    }

    if ((reg_num = get_register_number(operand)) != -1) {
        *value = reg_num;
        return true;
    }

    if (operand[0] == '*') {
        reg_num = get_register_number(operand + 1);
        if (reg_num != -1) {
            *value = reg_num;
            return true;
        }
    }

    // Symbol
    Symbol *symbol = get_symbol(operand);
    if (symbol) {
        *value = symbol->value;
        *is_external = (symbol->type == SYMBOL_EXTERNAL);
        return true;
    }

    fprintf(stderr, "Invalid operand: %s\n", operand);
    return false;
}

static const Instruction* find_instruction(const char *operation) {
    for (size_t i = 0; i < sizeof(instruction_set) / sizeof(Instruction); i++) {
        if (strcmp(operation, instruction_set[i].name) == 0) {
            return &instruction_set[i];
        }
    }
    return NULL;
}