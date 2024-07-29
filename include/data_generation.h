#ifndef DATA_GENERATION_H
#define DATA_GENERATION_H

#include <stdbool.h>
#include <stdio.h>

/* Constants */
#define MAX_DATA_SIZE 1000
#define MAX_DATA_VALUE 8191  // Maximum positive value for 14-bit signed integer
#define MIN_DATA_VALUE -8192 // Minimum negative value for 14-bit signed integer

/* Function Prototypes */

/* Process .data directive */
bool process_data_directive(const char *operands);

/* Process .string directive */
bool process_string_directive(const char *operands);

/* Reset the data counter */
void reset_data_counter();

/* Get the current value of the data counter */
int get_data_counter();

/* Write the data image to the output file */
void write_data_image(FILE *file);

/* Helper functions */
static bool validate_number(long value);
static bool add_to_data_image(int value);

/* Extern declarations for functions from other modules that data_generation.c might use */
extern int string_to_int(const char *str, bool *success);
extern void trim(char *str);

#endif /* DATA_GENERATION_H */