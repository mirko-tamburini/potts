# --- Compiler and Flags ---
CC      = gcc
CFLAGS  = -Wall -Wextra -O3 -Iinclude -Iutils
LDFLAGS = -lm

# --- Directories ---
SRC_DIR   = src
UTILS_DIR = utils
INC_DIR   = include
OBJ_DIR   = obj

# --- Files ---
# Project-specific logic in src/ plus the ran2 library in utils/
SRCS   = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(UTILS_DIR)/*.c)
# This logic turns src/file.c -> obj/file.o
OBJS   = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

TARGET = potts_sim

# --- Build Rules ---

all: $(TARGET)

run: all
	./$(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule for compiling files from src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for compiling files from utils/
$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the obj directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Professional 'clean' rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean