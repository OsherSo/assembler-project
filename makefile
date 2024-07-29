# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -g

# Directories
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin

# Source files and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Header files
DEPS := $(wildcard $(INC_DIR)/*.h)

# Executable name
TARGET := $(BIN_DIR)/assembler

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Rule to create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Include dependencies
-include $(OBJS:.o=.d)

# Rule to generate dependency files
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@set -e; rm -f $@; \
	$(CC) -MM -I$(INC_DIR) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(OBJ_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Debug target
debug: CFLAGS += -DDEBUG
debug: all

# Help target
help:
	@echo "Available targets:"
	@echo "  all    : Build the assembler (default target)"
	@echo "  clean  : Remove all generated files"
	@echo "  debug  : Build with debug symbols and DEBUG macro defined"
	@echo "  help   : Display this help message"