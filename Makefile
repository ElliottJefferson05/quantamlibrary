CC := gcc
BUILD_DIR := build
BINARY := quantom
TARGET := $(BUILD_DIR)/$(BINARY)
TEST_TARGET := $(BUILD_DIR)/tests/Quantom_test

CFLAGS := -Wall -Wextra -std=c11 -g
CPPFLAGS := -I. -Itests
LDLIBS := -lm

SRC := \
	main.c \
	quantomlibrary.c \
	circuit_Display.c \
	measurement.c \
	gates/matrix_gates.c \
	mathimatical_operations/operations.c

LIB_SRC := \
	quantomlibrary.c \
	circuit_Display.c \
	measurement.c \
	gates/matrix_gates.c \
	mathimatical_operations/operations.c

TEST_SRC := \
	tests/Quantom_test.c \
	tests/unity.c \
	$(LIB_SRC)

OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))
TEST_OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(TEST_SRC))
DEP := $(OBJ:.o=.d) $(TEST_OBJ:.o=.d)
LEGACY_OBJ := $(SRC:.c=.o)
LEGACY_DEP := $(LEGACY_OBJ:.o=.d)

.PHONY: all quantom run test clean

all: $(TARGET)

quantom: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDLIBS)

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(LEGACY_OBJ) $(LEGACY_DEP)

-include $(DEP)
