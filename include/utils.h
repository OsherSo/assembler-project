#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/* Constants */
#define MAX_LINE_LENGTH 80
#define MAX_LABEL_LENGTH 31
#define MAX_OPERATION_LENGTH 10
#define MAX_OPERAND_LENGTH 20

/* Function Prototypes */

/* Check if a line is empty or a comment */
bool is_empty_or_comment(const char *line);

/* Parse a line into label, operation, and operands */
bool parse_line(const char *line, char *label, char *operation, char *operands);

/* Remove leading and trailing whitespace from a string */
void trim(char *str);

/* Convert a string to an integer, checking for validity and range */
int string_to_int(const char *str, bool *success);

/* Check if a label is valid */
bool is_valid_label(const char *label);

/* Check if a word is a reserved word in the assembly language */
bool is_reserved_word(const char *word);

/* Convert an integer to its binary string representation */
void int_to_binary_string(int value, char *binary, int num_bits);

/* Convert a binary string to an integer */
int binary_string_to_int(const char *binary);

/* Check if a string represents a valid integer within the specified range */
bool is_valid_integer(const char *str, int min, int max);

/* Function to log errors */
void log_error(const char *format, ...);

/* Function to log warnings */
void log_warning(const char *format, ...);

#endif /* UTILS_H */