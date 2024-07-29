#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "second_pass.h"
#include "symbol_table.h"
#include "code_generation.h"
#include "utils.h"
#include "constants.h"

extern int IC;  /* Instruction Counter */
extern int DC;  /* Data Counter */

static int instruction_counter = MEMORY_START;

bool second_pass(const char *input_filename, const char *ob_filename, 
                 const char *ext_filename, const char *ent_filename) {
    FILE *input_file, *ob_file, *ext_file, *ent_file;
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    bool success = true;

    input_file = fopen(input_filename, "r");
    ob_file = fopen(ob_filename, "w");
    ext_file = fopen(ext_filename, "w");
    ent_file = fopen(ent_filename, "w");

    if (!input_file || !ob_file || !ext_file || !ent_file) {
        fprintf(stderr, "Error opening files for second pass\n");
        return false;
    }

    /* Write header to object file */
    fprintf(ob_file, "%d %d\n", IC - MEMORY_START, DC);

    while (fgets(line, sizeof(line), input_file)) {
        line_number++;
        line[strcspn(line, "\n")] = 0;  /* Remove newline character */

        if (is_empty_or_comment(line)) {
            continue;
        }

        if (!process_line_second_pass(line, line_number, ob_file, ext_file, ent_file)) {
            fprintf(stderr, "Error in line %d: %s\n", line_number, line);
            success = false;
        }
    }

    write_data_section(ob_file);

    fclose(input_file);
    fclose(ob_file);
    fclose(ext_file);
    fclose(ent_file);

    return success;
}

bool process_line_second_pass(const char *line, int line_number, FILE *ob_file, FILE *ext_file, FILE *ent_file) {
    char label[MAX_LABEL_LENGTH] = {0};
    char operation[MAX_OPERATION_LENGTH] = {0};
    char operands[MAX_LINE_LENGTH] = {0};

    (void)line_number; /* Suppress unused parameter warning */

    if (!parse_line(line, label, operation, operands)) {
        return false;
    }

    if (is_directive(operation)) {
        if (strcmp(operation, "entry") == 0) {
            return process_entry(operands, ent_file);
        }
        /* Skip other directives in second pass */
        return true;
    } else {
        return process_instruction_second_pass(operation, operands, ob_file, ext_file);
    }
}

bool process_entry(const char *operands, FILE *ent_file) {
    Symbol *symbol = get_symbol(operands);
    if (!symbol) {
        fprintf(stderr, "Entry symbol %s not found\n", operands);
        return false;
    }
    fprintf(ent_file, "%s %04d\n", operands, symbol->value);
    return true;
}

bool process_instruction_second_pass(const char *operation, const char *operands, FILE *ob_file, FILE *ext_file) {
    MachineCode code;
    if (!generate_machine_code(operation, operands, &code)) {
        return false;
    }

    /* Write machine code to object file */
    fprintf(ob_file, "%04d %05o\n", instruction_counter, code.first_word);
    instruction_counter++;

    if (code.second_word_exists) {
        fprintf(ob_file, "%04d %05o\n", instruction_counter, code.second_word);
        instruction_counter++;
    }

    if (code.third_word_exists) {
        fprintf(ob_file, "%04d %05o\n", instruction_counter, code.third_word);
        instruction_counter++;
    }

    /* Handle external references */
    if (code.is_external_reference) {
        fprintf(ext_file, "%s %04d\n", code.external_symbol, instruction_counter - 1);
    }

    return true;
}

void write_data_section(FILE *ob_file) {
    /* Write data section to object file */
    /* This function should iterate through the data image and write it to the object file */
    /* Implement based on your data storage mechanism */
    (void)ob_file; /* Suppress unused parameter warning */
}