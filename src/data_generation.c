#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data_generation.h"

#define MAX_DATA_SIZE 1000

static int data_image[MAX_DATA_SIZE];
static int data_counter = 0;

bool process_data_directive(const char *operands) {
    char *token;
    char *rest = strdup(operands);
    
    if (!rest) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }

    while ((token = strtok_r(rest, ",", &rest))) {
        // Remove leading and trailing whitespace
        while (isspace(*token)) token++;
        char *end = token + strlen(token) - 1;
        while (end > token && isspace(*end)) end--;
        *(end + 1) = 0;

        // Convert to integer
        char *endptr;
        long value = strtol(token, &endptr, 10);

        if (*endptr != '\0') {
            fprintf(stderr, "Invalid number in .data directive: %s\n", token);
            free(rest);
            return false;
        }

        if (value < -8192 || value > 8191) {
            fprintf(stderr, "Number out of range in .data directive: %ld\n", value);
            free(rest);
            return false;
        }

        if (data_counter >= MAX_DATA_SIZE) {
            fprintf(stderr, "Data segment full\n");
            free(rest);
            return false;
        }

        data_image[data_counter++] = (int)value;
    }

    free(rest);
    return true;
}

bool process_string_directive(const char *operands) {
    // Remove leading and trailing whitespace
    while (isspace(*operands)) operands++;
    const char *end = operands + strlen(operands) - 1;
    while (end > operands && isspace(*end)) end--;

    // Check if the string is properly enclosed in quotes
    if (*operands != '"' || *end != '"' || operands == end) {
        fprintf(stderr, "Invalid string format in .string directive\n");
        return false;
    }

    // Process the string content
    for (const char *c = operands + 1; c < end; c++) {
        if (data_counter >= MAX_DATA_SIZE) {
            fprintf(stderr, "Data segment full\n");
            return false;
        }
        data_image[data_counter++] = (int)*c;
    }

    // Add null terminator
    if (data_counter >= MAX_DATA_SIZE) {
        fprintf(stderr, "Data segment full\n");
        return false;
    }
    data_image[data_counter++] = 0;

    return true;
}

void reset_data_counter() {
    data_counter = 0;
}

int get_data_counter() {
    return data_counter;
}

void write_data_image(FILE *file) {
    for (int i = 0; i < data_counter; i++) {
        fprintf(file, "%04d %05o\n", i + 100, data_image[i] & 0x7FFF);
    }
}