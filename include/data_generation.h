#ifndef DATA_GENERATION_H
#define DATA_GENERATION_H

#include <stdbool.h>
#include <stdio.h>

/* Constants */
#define MAX_DATA_SIZE 1000
#define MAX_DATA_VALUE 8191  // Maximum positive value for 14-bit signed integer
#define MIN_DATA_VALUE -8192 // Minimum negative value for 14-bit signed integer

/* Function Prototypes */

bool process_data_directive(const char *operands);
bool process_string_directive(const char *operands);
bool process_entry_extern_directive(const char *directive, const char *operands);
void reset_data_counter();
int get_data_counter();
void write_data_image(FILE *file);

#endif /* DATA_GENERATION_H */