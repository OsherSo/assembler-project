#ifndef CODE_GENERATION_H
#define CODE_GENERATION_H

#include <stdbool.h>
#include "constants.h"

typedef struct {
    const char *name;
    int opcode;
    int operand_count;
} Instruction;

/* Function Prototypes */

/**
 * Generates machine code for a given operation and its operands.
 * 
 * @param operation The assembly operation (e.g., "mov", "add")
 * @param operands The operands for the operation
 * @param code Pointer to a MachineCode struct to store the generated code
 * @return true if code generation was successful, false otherwise
 */
bool generate_machine_code(const char *operation, const char *operands, MachineCode *code);

/**
 * Determines the addressing mode of a given operand.
 * 
 * @param operand The operand to analyze
 * @return The addressing mode as defined in the AddressingMode enum
 */
AddressingMode get_addressing_mode(const char *operand);

/**
 * Encodes an individual operand into its machine code representation.
 * 
 * @param operand The operand to encode
 * @param value Pointer to store the encoded value
 * @param is_external Pointer to a bool indicating if the operand is an external reference
 * @return true if encoding was successful, false otherwise
 */
bool encode_operand(const char *operand, int *value, bool *is_external);

#endif /* CODE_GENERATION_H */