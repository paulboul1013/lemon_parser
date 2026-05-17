CC=gcc
CFLAGS= -Wall -Wextra -std=c11 -Iinclude -Isrc

BUILD_DIR=build

GRAMMAR_SRC=src/grammar.c src/lr0.c
TEST_GRAMMAR_SRC = tests/test_grammar.c

TEST_GRAMMAR_BIN = $(BUILD_DIR)/test_grammar

.PHONY: all test clean

all: test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_GRAMMAR_BIN): $(GRAMMAR_SRC) $(TEST_GRAMMAR_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(GRAMMAR_SRC) $(TEST_GRAMMAR_SRC) -o $(TEST_GRAMMAR_BIN)

test: $(TEST_GRAMMAR_BIN)
	./$(TEST_GRAMMAR_BIN)

clean:
	rm *.o main