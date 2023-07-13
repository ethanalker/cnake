CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=gnu99
LIBS=-lm

SRC=src
OBJ=obj
FILES=cnake draw term utils

all: cnake

cnake: $(patsubst %,$(OBJ)/%.o,$(FILES)) $(SRC)/main.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h | $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $(patsubst $(OBJ)/%.o,$(SRC)/%.c,$@)

$(OBJ):
	mkdir $(OBJ)

clean:
	rm $(OBJ)/*.o cnake

.PHONY: all clean
