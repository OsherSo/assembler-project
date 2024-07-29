#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdbool.h>

/* Constants */
#define MAX_FILENAME 256

/* Function Prototypes */

/**
 * Main entry point for the assembler.
 * Processes each input file and generates output files.
 */
int main(int argc, char *argv[]);

/**
 * Cleans up any resources allocated during the assembly process.
 * Should be called before the program exits.
 */
void cleanup_resources();

/**
 * Performs the first pass of the assembly process.
 * Builds the symbol table and processes directives.
 */
bool first_pass(const char *filename);

/**
 * Performs the second pass of the assembly process.
 * Generates machine code and resolves symbols.
 */
bool second_pass(const char *input_filename, const char *ob_filename, 
                 const char *ext_filename, const char *ent_filename);

/**
 * Processes macros in the input file and generates an expanded source file.
 */
bool process_macros(const char *input_filename, const char *output_filename);

#endif /* ASSEMBLER_H */