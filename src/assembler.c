#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"
#include "first_pass.h"
#include "second_pass.h"
#include "macro_processor.h"
#include "utils.h"
#include "symbol_table.h"

#define MAX_FILENAME 256

static void process_file(const char *base_filename);
static void generate_output_filenames(const char *base_filename, char *am_filename, char *ob_filename, char *ext_filename, char *ent_filename);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        process_file(argv[i]);
    }

    return EXIT_SUCCESS;
}

static void process_file(const char *base_filename) {
    char input_filename[MAX_FILENAME];
    char am_filename[MAX_FILENAME];
    char ob_filename[MAX_FILENAME];
    char ext_filename[MAX_FILENAME];
    char ent_filename[MAX_FILENAME];

    snprintf(input_filename, MAX_FILENAME, "%s.as", base_filename);
    generate_output_filenames(base_filename, am_filename, ob_filename, ext_filename, ent_filename);

    printf("Processing file: %s\n", input_filename);

    if (!process_macros(input_filename, am_filename)) {
        fprintf(stderr, "Error processing macros in file %s\n", input_filename);
        return;
    }

    initialize_symbol_table();

    if (!first_pass(am_filename)) {
        fprintf(stderr, "Error in first pass for file %s\n", am_filename);
        return;
    }

    if (!second_pass(am_filename, ob_filename, ext_filename, ent_filename)) {
        fprintf(stderr, "Error in second pass for file %s\n", am_filename);
        return;
    }

    printf("Successfully assembled %s\n", input_filename);
    cleanup_resources();
}

static void generate_output_filenames(const char *base_filename, char *am_filename, char *ob_filename, char *ext_filename, char *ent_filename) {
    snprintf(am_filename, MAX_FILENAME, "%s.am", base_filename);
    snprintf(ob_filename, MAX_FILENAME, "%s.ob", base_filename);
    snprintf(ext_filename, MAX_FILENAME, "%s.ext", base_filename);
    snprintf(ent_filename, MAX_FILENAME, "%s.ent", base_filename);
}

void cleanup_resources() {
    /* Free any global resources, close files, etc. */
    /* This function should be implemented based on your specific needs */
}