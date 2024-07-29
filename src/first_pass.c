#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "first_pass.h"
#include "symbol_table.h"
#include "utils.h"
#include "constants.h"
#include "data_generation.h"

int IC = MEMORY_START;  /* Instruction Counter */
int DC = 0;  /* Data Counter */

static bool process_label(const char *label);
static bool process_directive(const char *directive, const char *operands);
static bool process_instruction(const char *operation, const char *operands);
static int calculate_instruction_length(const char *operation, const char *operands);

bool first_pass(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    bool success = true;

    if (!file) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return false;
    }

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        line[strcspn(line, "\n")] = 0;  /* Remove newline character */

        if (is_empty_or_comment(line)) {
            continue;
        }

        if (!process_line(line, line_number)) {
            fprintf(stderr, "Error in line %d: %s\n", line_number, line);
            success = false;
        }
    }

    fclose(file);
    update_data_symbols(IC);
    return success;
}

bool process_line(const char *line, int line_number __attribute__((unused))) {
    char label[MAX_LABEL_LENGTH] = {0};
    char operation[MAX_OPERATION_LENGTH] = {0};
    char operands[MAX_LINE_LENGTH] = {0};

    if (!parse_line(line, label, operation, operands)) {
        return false;
    }

    if (label[0] != '\0' && !process_label(label)) {
        return false;
    }

    if (is_directive(operation)) {
        return process_directive(operation, operands);
    } else {
        return process_instruction(operation, operands);
    }
}

static bool process_label(const char *label) {
    if (!is_valid_label(label)) {
        fprintf(stderr, "Invalid label: %s\n", label);
        return false;
    }
    return add_symbol(label, IC, SYMBOL_CODE);
}

static bool process_directive(const char *directive, const char *operands) {
    if (strcmp(directive, "data") == 0) {
        return process_data_directive(operands);
    } else if (strcmp(directive, "string") == 0) {
        return process_string_directive(operands);
    } else if (strcmp(directive, "entry") == 0 || strcmp(directive, "extern") == 0) {
        return process_entry_extern_directive(directive, operands);
    }
    fprintf(stderr, "Unknown directive: %s\n", directive);
    return false;
}

static bool process_instruction(const char *operation, const char *operands) {
    int instruction_length = calculate_instruction_length(operation, operands);
    if (instruction_length == -1) {
        return false;
    }
    IC += instruction_length;
    return true;
}

static int calculate_instruction_length(const char *operation, const char *operands) {
    /* Implement logic to determine instruction length based on operation and operands */
    /* This is a placeholder implementation */
    (void)operation; /* Suppress unused parameter warning */
    (void)operands;  /* Suppress unused parameter warning */
    return 1;  /* Assume all instructions are 1 word long for simplicity */
}