#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include <stdbool.h>
#include <stdio.h>
#include "symbol_table.h"
#include "constants.h"

/* Function Prototypes */

/* Main function for the second pass */
bool second_pass(const char *input_filename, const char *ob_filename, 
                 const char *ext_filename, const char *ent_filename);

/* Helper functions */
bool process_line_second_pass(const char *line, int line_number, FILE *ob_file, FILE *ext_file, FILE *ent_file);
bool process_entry(const char *operands, FILE *ent_file);
bool process_instruction_second_pass(const char *operation, const char *operands, FILE *ob_file, FILE *ext_file);
void write_data_section(FILE *ob_file);

/* Utility function */
bool is_directive(const char *operation);

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