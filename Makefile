CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=gnu99
DFLAGS=-g
RFLAGS=-O2 -DNDEBUG
CLIBS=-lm

SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BIN=cnake

all: build

build: CFLAGS:=$(CFLAGS) $(DFLAGS)
build: $(BIN)

release: CFLAGS:=$(CFLAGS) $(RFLAGS)
release: clean
release: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(CLIBS) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) $(CLIBS) -c -o $@ $^

$(OBJ):
	mkdir $(OBJ)

clean:
	-rm $(OBJ)/* $(BIN)

run: $(BIN)
	-${TERM} -e ./$^ > /dev/null 2>&1 &

gdb: run
	sleep 3
	sh -c 'gdb -p $$(pidof cnake)'

debug: gdb

.PHONY: all clean run gdb debug
