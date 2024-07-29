#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/* Function Prototypes */

bool is_empty_or_comment(const char *line);
bool parse_line(const char *line, char *label, char *operation, char *operands);
void trim(char *str);
int string_to_int(const char *str, bool *success);
bool is_valid_label(const char *label);
bool is_reserved_word(const char *word);
void int_to_binary_string(int value, char *binary, int num_bits);
int binary_string_to_int(const char *binary);
bool is_valid_integer(const char *str, int min, int max);
void log_error(const char *format, ...);
void log_warning(const char *format, ...);
bool is_directive(const char *operation);

#endif /* UTILS_H */