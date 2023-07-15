CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=gnu99 -g
LIBS=-lm

SRC=src
OBJ=obj
FILES=cnake draw term utils io

all: cnake

cnake: $(patsubst %,$(OBJ)/%.o,$(FILES)) $(SRC)/main.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h | $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $(patsubst $(OBJ)/%.o,$(SRC)/%.c,$@)

$(OBJ):
	mkdir $(OBJ)

clean:
	rm $(OBJ)/*.o cnake

run: cnake
	${TERM} -e ./$^ &

gdb: run
	sleep 3
	sh -c 'gdb -p $$(pidof cnake)'

debug: gdb

.PHONY: all clean run gdb debug
