#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "utils.h"
#include "constants.h"

bool is_empty_or_comment(const char *line) {
    while (*line) {
        if (!isspace(*line)) {
            return (*line == ';');  // True if it's a comment, false otherwise
        }
        line++;
    }
    return true;  // Empty line
}

bool parse_line(const char *line, char *label, char *operation, char *operands) {
    const char *start = line;
    
    // Skip leading whitespace
    while (isspace(*start)) start++;

    // Check for empty line or comment
    if (*start == '\0' || *start == ';') {
        *label = *operation = *operands = '\0';
        return true;
    }

    // Parse label
    const char *colon = strchr(start, ':');
    if (colon) {
        size_t label_length = colon - start;
        if (label_length >= MAX_LABEL_LENGTH) {
            log_error("Label too long: %.*s", (int)label_length, start);
            return false;
        }
        strncpy(label, start, label_length);
        label[label_length] = '\0';
        start = colon + 1;
    } else {
        *label = '\0';
    }

    // Skip whitespace after label
    while (isspace(*start)) start++;

    // Parse operation
    const char *space = strchr(start, ' ');
    if (space) {
        size_t operation_length = space - start;
        if (operation_length >= MAX_OPERATION_LENGTH) {
            log_error("Operation too long: %.*s", (int)operation_length, start);
            return false;
        }
        strncpy(operation, start, operation_length);
        operation[operation_length] = '\0';
        start = space + 1;
    } else {
        strcpy(operation, start);
        *operands = '\0';
        return true;
    }

    // Skip whitespace after operation
    while (isspace(*start)) start++;

    // Parse operands
    strncpy(operands, start, MAX_LINE_LENGTH - 1);
    operands[MAX_LINE_LENGTH - 1] = '\0';
    trim(operands);

    return true;
}

void trim(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
        return;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';
}

int string_to_int(const char *str, bool *success) {
    char *endptr;
    long value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        *success = false;
        return 0;
    }

    if (value < MIN_NEGATIVE_VALUE || value > MAX_POSITIVE_VALUE) {
        *success = false;
        return 0;
    }

    *success = true;
    return (int)value;
}

bool is_valid_label(const char *label) {
    if (!isalpha(*label)) {
        return false;  // First character must be a letter
    }

    size_t len = strlen(label);
    if (len > MAX_LABEL_LENGTH) {
        return false;  // Label is too long
    }

    for (size_t i = 1; i < len; i++) {
        if (!isalnum(label[i])) {
            return false;  // Must contain only letters and digits
        }
    }

    return !is_reserved_word(label);
}

bool is_reserved_word(const char *word) {
    static const char *reserved_words[] = {
        "mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec",
        "jmp", "bne", "red", "prn", "jsr", "rts", "stop", "data", "string",
        "entry", "extern", "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"
    };
    static const int num_reserved_words = sizeof(reserved_words) / sizeof(reserved_words[0]);

    for (int i = 0; i < num_reserved_words; i++) {
        if (strcmp(word, reserved_words[i]) == 0) {
            return true;
        }
    }
    return false;
}

void int_to_binary_string(int value, char *binary, int num_bits) {
    for (int i = num_bits - 1; i >= 0; i--) {
        binary[num_bits - 1 - i] = (value & (1 << i)) ? '1' : '0';
    }
    binary[num_bits] = '\0';
}

int binary_string_to_int(const char *binary) {
    int result = 0;
    while (*binary) {
        result = (result << 1) + (*binary - '0');
        binary++;
    }
    return result;
}

bool is_valid_integer(const char *str, int min, int max) {
    char *endptr;
    long value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        return false;  // Not a valid integer
    }

    return (value >= min && value <= max);
}

void log_error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void log_warning(const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

bool is_directive(const char *operation) {
    return (strcmp(operation, "data") == 0 ||
            strcmp(operation, "string") == 0 ||
            strcmp(operation, "entry") == 0 ||
            strcmp(operation, "extern") == 0);
}