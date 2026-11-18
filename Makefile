CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2 -MMD -MP -Ilibs/raylib/include
LDFLAGS = -Llibs/raylib/lib
LIBS    = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC_DIR   = src
BUILD_DIR = build
TARGET    = tetris

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

compdb:
	bear -- $(MAKE) -B

clean:
	rm -rf $(BUILD_DIR) $(TARGET) compile_commands.json

-include $(DEP)

.PHONY: clean compdb