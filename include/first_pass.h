#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdbool.h>
#include "constants.h"

/* Function Prototypes */

/* Main function for the first pass */
bool first_pass(const char *filename);

/* Helper functions */
bool process_line(const char *line, int line_number);

/* Extern declarations for functions from other modules that first_pass.c might use */
extern bool add_symbol(const char *name, int value, SymbolType type);
extern bool is_valid_label(const char *label);
extern bool is_reserved_word(const char *word);
extern void update_data_symbols(int ic_value);
extern bool process_data_directive(const char *operands);
extern bool process_string_directive(const char *operands);
extern bool process_entry_extern_directive(const char *directive, const char *operands);

/* Extern declarations for global variables that first_pass.c might use */
extern int IC;  /* Instruction Counter */
extern int DC;  /* Data Counter */

#endif /* FIRST_PASS_H */