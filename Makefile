# Makefile for a simple C project

# Compiler and compiler flags
CC := gcc
CFLAGS := -Wall -Wextra -lsensors -lncurses

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Source files and object files
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Executable name
EXECUTABLE := $(BIN_DIR)/app

# Default target
all: $(EXECUTABLE)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into the final executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Create necessary directories
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

run:
	./$(EXECUTABLE)