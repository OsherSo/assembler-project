#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdbool.h>

/* Constants */
#define MAX_LINE_LENGTH 80
#define MAX_LABEL_LENGTH 31
#define MAX_OPERATION_LENGTH 10

/* Function Prototypes */

/* Main function for the first pass */
bool first_pass(const char *filename);

/* Helper functions */
static bool process_line(const char *line, int line_number);
static bool process_data(const char *operands);
static bool process_string(const char *operands);
static bool process_entry_extern(const char *operation, const char *operands);
static bool process_instruction(const char *operation, const char *operands);
static int get_instruction_length(const char *operation, const char *operands);

/* Extern declarations for functions from other modules that first_pass.c might use */
extern bool add_symbol(const char *name, int value, int type);
extern bool is_valid_label(const char *label);
extern bool is_reserved_word(const char *word);
extern void update_data_symbols(int ic_value);

/* Extern declarations for global variables that first_pass.c might use */
extern int IC;  /* Instruction Counter */
extern int DC;  /* Data Counter */

#endif /* FIRST_PASS_H */