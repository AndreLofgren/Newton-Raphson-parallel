SHELL=/bin/bash
CC=gcc
CFLAGS=-O2 -fopenmp
LIBS=-lm -fopenmp
OUT_DIR=bin obj

.PHONY: directories main all clean

all: directories main

directories: $(OUT_DIR)

$(OUT_DIR):
	mkdir -p ./$@

obj/bisection.o: ./src/bisection.c
	$(CC) -c $(CFLAGS) $< -o $@

obj/newton-bisection.o: ./src/newton-bisection.c
	$(CC) -c $(CFLAGS) $< -o $@

obj/main.o: ./src/main.c
	$(CC) -c $(CFLAGS) $< -o $@

main: ./obj/bisection.o ./obj/newton-bisection.o ./obj/main.o
	$(CC) $^ $(LIBS) -o ./bin/$@

clean:
	rm -rf $(OUT_DIR)
