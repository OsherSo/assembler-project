#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>
#include "constants.h"

#define MAX_SYMBOLS 1000
#define MAX_ENTRIES 100

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

void initialize_symbol_table();
bool add_symbol(const char *name, int value, SymbolType type);
Symbol *get_symbol(const char *name);
bool update_symbol_value(const char *name, int new_value);
void update_data_symbols(int ic_value);
void print_symbol_table();
bool is_external_symbol(const char *name);
void get_entry_symbols(EntrySymbol *entries, int *count);
void free_symbol_table();

#endif /* SYMBOL_TABLE_H */