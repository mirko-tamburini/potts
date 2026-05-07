# --- Compiler and Flags ---
CC      = gcc
CFLAGS  = -Wall -Wextra -O3 -Iinclude -Iutils
LDFLAGS = -lm

# --- Directories ---
SRC_DIR   = src
UTILS_DIR = utils
INC_DIR   = include
OBJ_DIR   = obj
BIN_DIR   = bin
OUT_DIR   = output

# --- Target ---
TARGET = $(BIN_DIR)/potts_sim

# --- Files ---
# Collects all .c files from both source folders:
# Project-specific logic in src/ plus the ran2 library in utils/
SRCS   = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(UTILS_DIR)/*.c)

# Converts the list of source files into object files inside OBJ_DIR
# e.g., src/main.c -> obj/main.o
OBJS   = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

# --- Build Rules ---

all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule for compiling files from src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for compiling files from utils/
$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Run the simulation
run: all | $(OUT_DIR)
	./$(TARGET)

# Professional 'clean' rule
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(OUT_DIR)

.PHONY: all clean run