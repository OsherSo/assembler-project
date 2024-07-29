#ifndef MACRO_PROCESSOR_H
#define MACRO_PROCESSOR_H

#include <stdbool.h>
#include <stdio.h>
#include "constants.h"

/* Function Prototypes */

/* Main function to process macros */
bool process_macros(const char *input_filename, const char *output_filename);

/* Helper functions */
bool is_macro_definition(const char *line, char *macro_name);
bool is_macro_end(const char *line);
bool is_macro_call(const char *line, char *macro_name);
bool add_macro(const char *name, FILE *input);
bool expand_macro(const char *name, FILE *output);

/* Extern declarations for functions from other modules that macro_processor.c might use */
extern bool is_empty_or_comment(const char *line);
extern void trim(char *str);

#endif /* MACRO_PROCESSOR_H */