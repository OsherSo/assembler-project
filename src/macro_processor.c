#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_processor.h"

#define MAX_MACRO_NAME 31
#define MAX_MACRO_LINES 100
#define MAX_LINE_LENGTH 80
#define MAX_MACROS 100

typedef struct {
    char name[MAX_MACRO_NAME + 1];
    char lines[MAX_MACRO_LINES][MAX_LINE_LENGTH + 1];
    int line_count;
} Macro;

static Macro macro_table[MAX_MACROS];
static int macro_count = 0;

static Macro *find_macro(const char *name);

bool process_macros(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    FILE *output = fopen(output_filename, "w");
    char line[MAX_LINE_LENGTH + 1];
    char macro_name[MAX_MACRO_NAME + 1];

    if (!input || !output) {
        fprintf(stderr, "Error opening files for macro processing\n");
        return false;
    }

    while (fgets(line, sizeof(line), input)) {
        if (is_macro_definition(line, macro_name)) {
            if (!add_macro(macro_name, input)) {
                fclose(input);
                fclose(output);
                return false;
            }
        } else if (is_macro_call(line, macro_name)) {
            if (!expand_macro(macro_name, output)) {
                fclose(input);
                fclose(output);
                return false;
            }
        } else {
            fputs(line, output);
        }
    }

    fclose(input);
    fclose(output);
    return true;
}

bool is_macro_definition(const char *line, char *macro_name) {
    return (sscanf(line, "macro %s", macro_name) == 1);
}

bool is_macro_end(const char *line) {
    return (strncmp(line, "endmacro", 8) == 0);
}

bool is_macro_call(const char *line, char *macro_name) {
    for (int i = 0; i < macro_count; i++) {
        if (strncmp(line, macro_table[i].name, strlen(macro_table[i].name)) == 0) {
            strcpy(macro_name, macro_table[i].name);
            return true;
        }
    }
    return false;
}

bool add_macro(const char *name, FILE *input) {
    if (macro_count >= MAX_MACROS) {
        fprintf(stderr, "Maximum number of macros exceeded\n");
        return false;
    }

    if (find_macro(name)) {
        fprintf(stderr, "Macro '%s' already defined\n", name);
        return false;
    }

    Macro *macro = &macro_table[macro_count++];
    strncpy(macro->name, name, MAX_MACRO_NAME);
    macro->name[MAX_MACRO_NAME] = '\0';
    macro->line_count = 0;

    char line[MAX_LINE_LENGTH + 1];
    while (fgets(line, sizeof(line), input) && !is_macro_end(line)) {
        if (macro->line_count < MAX_MACRO_LINES) {
            strncpy(macro->lines[macro->line_count], line, MAX_LINE_LENGTH);
            macro->lines[macro->line_count][MAX_LINE_LENGTH] = '\0';
            macro->line_count++;
        } else {
            fprintf(stderr, "Macro '%s' exceeds maximum lines\n", name);
            return false;
        }
    }

    return true;
}

bool expand_macro(const char *name, FILE *output) {
    Macro *macro = find_macro(name);
    if (!macro) {
        fprintf(stderr, "Macro '%s' not found\n", name);
        return false;
    }

    for (int i = 0; i < macro->line_count; i++) {
        fputs(macro->lines[i], output);
    }
    return true;
}

static Macro *find_macro(const char *name) {
    for (int i = 0; i < macro_count; i++) {
        if (strcmp(macro_table[i].name, name) == 0) {
            return &macro_table[i];
        }
    }
    return NULL;
}