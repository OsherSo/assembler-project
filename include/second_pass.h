#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include <stdbool.h>
#include <stdio.h>

#include "symbol_table.h"

/* Constants */
#define MAX_LINE_LENGTH 80
#define MAX_LABEL_LENGTH 31
#define MAX_OPERATION_LENGTH 10
#define MAX_OPERAND_LENGTH 20

/* Structs */
typedef struct {
    int first_word;
    int second_word;
    int third_word;
    bool second_word_exists;
    bool third_word_exists;
    bool is_external_reference;
    char external_symbol[MAX_LABEL_LENGTH + 1];
} MachineCode;

/* Function Prototypes */

/* Main function for the second pass */
bool second_pass(const char *input_filename, const char *ob_filename, 
                 const char *ext_filename, const char *ent_filename);

/* Helper functions */
static bool process_line_second_pass(const char *line, int line_number, FILE *ob_file, FILE *ext_file, FILE *ent_file);
static bool process_entry(const char *operands, FILE *ent_file);
static bool process_instruction_second_pass(const char *operation, const char *operands, FILE *ob_file, FILE *ext_file);
static void write_data_section(FILE *ob_file);

/* Extern declarations for functions from other modules that second_pass.c might use */
extern bool generate_machine_code(const char *operation, const char *operands, MachineCode *code);
extern bool is_empty_or_comment(const char *line);
extern bool parse_line(const char *line, char *label, char *operation, char *operands);
extern Symbol *get_symbol(const char *name);
extern bool is_external_symbol(const char *name);
extern void get_entry_symbols(EntrySymbol *entries, int *count);

/* Extern declarations for global variables that second_pass.c might use */
extern int IC;  /* Instruction Counter */
extern int DC;  /* Data Counter */

#endif /* SECOND_PASS_H */