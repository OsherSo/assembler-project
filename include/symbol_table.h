#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>

/* Constants */
#define MAX_SYMBOLS 1000
#define MAX_SYMBOL_LENGTH 31
#define MAX_ENTRIES 100

/* Enums */
typedef enum {
    SYMBOL_CODE,
    SYMBOL_DATA,
    SYMBOL_EXTERNAL,
    SYMBOL_ENTRY
} SymbolType;

/* Structs */
typedef struct {
    char name[MAX_SYMBOL_LENGTH + 1];
    int value;
    SymbolType type;
} Symbol;

typedef struct {
    char name[MAX_SYMBOL_LENGTH + 1];
    int value;
} EntrySymbol;

/* Function Prototypes */

/* Initialize the symbol table */
void initialize_symbol_table();

/* Add a new symbol to the table */
bool add_symbol(const char *name, int value, SymbolType type);

/* Get a symbol from the table */
Symbol *get_symbol(const char *name);

/* Update the value of an existing symbol */
bool update_symbol_value(const char *name, int new_value);

/* Update all data symbols by adding the final IC value */
void update_data_symbols(int ic_value);

/* Print the entire symbol table (for debugging) */
void print_symbol_table();

/* Check if a symbol is marked as external */
bool is_external_symbol(const char *name);

/* Get all symbols marked as entries */
void get_entry_symbols(EntrySymbol *entries, int *count);

#endif /* SYMBOL_TABLE_H */