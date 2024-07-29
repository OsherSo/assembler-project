#ifndef MACRO_PROCESSOR_H
#define MACRO_PROCESSOR_H

#include <stdbool.h>

/* Constants */
#define MAX_MACRO_NAME 31
#define MAX_MACRO_LINES 100
#define MAX_LINE_LENGTH 80
#define MAX_MACROS 100

/* Structs */
typedef struct {
    char name[MAX_MACRO_NAME + 1];
    char lines[MAX_MACRO_LINES][MAX_LINE_LENGTH + 1];
    int line_count;
} Macro;

/* Function Prototypes */

/* Main function to process macros */
bool process_macros(const char *input_filename, const char *output_filename);

/* Helper functions */
static bool is_macro_definition(const char *line, char *macro_name);
static bool is_macro_end(const char *line);
static bool is_macro_call(const char *line, char *macro_name);
static void add_macro(const char *name, FILE *input);
static void expand_macro(const char *name, FILE *output);

/* Extern declarations for functions from other modules that macro_processor.c might use */
extern bool is_empty_or_comment(const char *line);
extern void trim(char *str);

#endif /* MACRO_PROCESSOR_H */