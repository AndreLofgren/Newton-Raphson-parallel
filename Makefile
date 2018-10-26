SHELL=/bin/bash
CC=gcc
CFLAGS=-O2 -fopenmp
LIBS=-lm
OUT_DIR=bin

.PHONY: directories all clean

all: directories bisection newton-bisection

directories: $(OUT_DIR)

$(OUT_DIR):
	mkdir -p ./$@

bisection: ./src/bisection.c
	$(CC) $(CFLAGS) $< $(LIBS) -o ./bin/$@

newton-bisection: ./src/newton-bisection.c
	$(CC) $(CFLAGS) $< $(LIBS) -o ./bin/$@

clean:
	rm -f ./bin/*
