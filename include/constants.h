#ifndef CONSTANTS_H
#define CONSTANTS_H

/* General constants */
#define WORD_SIZE 15
#define MEMORY_SIZE 4096
#define MAX_LINE_LENGTH 80
#define MAX_LABEL_LENGTH 31
#define MAX_OPERATION_LENGTH 10
#define MAX_OPERAND_LENGTH 20
#define MAX_FILENAME 256

/* Assembler limits */
#define MAX_SYMBOLS 1000
#define MAX_DATA_SIZE 1000
#define MAX_MACROS 100
#define MAX_MACRO_LINES 100

/* Memory addresses */
#define MEMORY_START 100

/* Data ranges */
#define MAX_POSITIVE_VALUE 8191  // 2^13 - 1, for 14-bit signed integer
#define MIN_NEGATIVE_VALUE -8192 // -2^13, for 14-bit signed integer

/* Assembler directives */
#define DIRECTIVE_DATA ".data"
#define DIRECTIVE_STRING ".string"
#define DIRECTIVE_ENTRY ".entry"
#define DIRECTIVE_EXTERN ".extern"

/* File extensions */
#define SOURCE_EXTENSION ".as"
#define OBJECT_EXTENSION ".ob"
#define ENTRIES_EXTENSION ".ent"
#define EXTERNALS_EXTENSION ".ext"
#define EXPANDED_SOURCE_EXTENSION ".am"

/* Enum for symbol types */
typedef enum {
    SYMBOL_UNKNOWN,
    SYMBOL_CODE,
    SYMBOL_DATA,
    SYMBOL_ENTRY,
    SYMBOL_EXTERNAL
} SymbolType;

/* Enum for addressing modes */
typedef enum {
    ADDR_IMMEDIATE,
    ADDR_DIRECT,
    ADDR_RELATIVE,
    ADDR_REGISTER
} AddressingMode;

/* Enum for A, R, E bits */
typedef enum {
    ARE_ABSOLUTE = 4,    // 100
    ARE_RELOCATABLE = 2, // 010
    ARE_EXTERNAL = 1     // 001
} AREType;

#endif /* CONSTANTS_H */