#ifndef CODE_GENERATION_H
#define CODE_GENERATION_H

#include <stdbool.h>

/* Constants */
#define MAX_OPERANDS 2
#define MAX_SYMBOL_LENGTH 31
#define MAX_OPERAND_LENGTH 20

/* Enums */
typedef enum {
    ADDRESSING_IMMEDIATE,
    ADDRESSING_DIRECT,
    ADDRESSING_REGISTER_INDIRECT,
    ADDRESSING_REGISTER_DIRECT
} AddressingMode;

/* Structs */
typedef struct {
    const char *name;
    int opcode;
    int operand_count;
} Instruction;

typedef struct {
    int first_word;
    int second_word;
    int third_word;
    bool second_word_exists;
    bool third_word_exists;
    bool is_external_reference;
    char external_symbol[MAX_SYMBOL_LENGTH + 1];
} MachineCode;

/* Function Prototypes */

/* Main function to generate machine code */
bool generate_machine_code(const char *operation, const char *operands, MachineCode *code);

/* Helper functions */
static int get_register_number(const char *reg);
static AddressingMode get_addressing_mode(const char *operand);
static bool encode_operand(const char *operand, int *value, bool *is_external);

/* Extern declarations for functions from other modules that code_generation.c might use */
extern Symbol *get_symbol(const char *name);
extern bool is_external_symbol(const char *name);

/* The instruction set */
extern const Instruction instruction_set[];

#endif /* CODE_GENERATION_H */