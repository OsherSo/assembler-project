#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

#define HASH_SIZE 101

typedef struct SymbolNode {
    Symbol symbol;
    struct SymbolNode *next;
} SymbolNode;

static SymbolNode *hash_table[HASH_SIZE] = {NULL};

static unsigned int hash(const char *str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % HASH_SIZE;
}

void initialize_symbol_table() {
    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

bool add_symbol(const char *name, int value, SymbolType type) {
    if (get_symbol(name) != NULL) {
        fprintf(stderr, "Symbol %s already exists\n", name);
        return false;
    }

    unsigned int index = hash(name);
    SymbolNode *new_node = (SymbolNode *)malloc(sizeof(SymbolNode));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }

    strncpy(new_node->symbol.name, name, MAX_SYMBOL_LENGTH - 1);
    new_node->symbol.name[MAX_SYMBOL_LENGTH - 1] = '\0';
    new_node->symbol.value = value;
    new_node->symbol.type = type;
    new_node->next = hash_table[index];
    hash_table[index] = new_node;

    return true;
}

Symbol *get_symbol(const char *name) {
    unsigned int index = hash(name);
    SymbolNode *current = hash_table[index];

    while (current) {
        if (strcmp(current->symbol.name, name) == 0) {
            return &(current->symbol);
        }
        current = current->next;
    }

    return NULL;
}

bool update_symbol_value(const char *name, int new_value) {
    Symbol *symbol = get_symbol(name);
    if (symbol == NULL) {
        return false;
    }
    symbol->value = new_value;
    return true;
}

void update_data_symbols(int ic_value) {
    for (int i = 0; i < HASH_SIZE; i++) {
        SymbolNode *current = hash_table[i];
        while (current) {
            if (current->symbol.type == SYMBOL_DATA) {
                current->symbol.value += ic_value;
            }
            current = current->next;
        }
    }
}

void print_symbol_table() {
    printf("Symbol Table:\n");
    printf("Name\t\tValue\tType\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        SymbolNode *current = hash_table[i];
        while (current) {
            printf("%-15s\t%d\t", current->symbol.name, current->symbol.value);
            switch (current->symbol.type) {
                case SYMBOL_CODE: printf("Code\n"); break;
                case SYMBOL_DATA: printf("Data\n"); break;
                case SYMBOL_EXTERNAL: printf("External\n"); break;
                case SYMBOL_ENTRY: printf("Entry\n"); break;
                case SYMBOL_UNKNOWN: printf("Unknown\n"); break;
            }
            current = current->next;
        }
    }
}

bool is_external_symbol(const char *name) {
    Symbol *symbol = get_symbol(name);
    return symbol != NULL && symbol->type == SYMBOL_EXTERNAL;
}

void get_entry_symbols(EntrySymbol *entries, int *count) {
    *count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        SymbolNode *current = hash_table[i];
        while (current && *count < MAX_ENTRIES) {
            if (current->symbol.type == SYMBOL_ENTRY) {
                strncpy(entries[*count].name, current->symbol.name, MAX_SYMBOL_LENGTH - 1);
                entries[*count].name[MAX_SYMBOL_LENGTH - 1] = '\0';
                entries[*count].value = current->symbol.value;
                (*count)++;
            }
            current = current->next;
        }
    }
}

void free_symbol_table() {
    for (int i = 0; i < HASH_SIZE; i++) {
        SymbolNode *current = hash_table[i];
        while (current) {
            SymbolNode *temp = current;
            current = current->next;
            free(temp);
        }
        hash_table[i] = NULL;
    }
}