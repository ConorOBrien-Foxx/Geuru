CC=gcc
CFLAGS=-I.
DEPS=src/stack.h src/atom.h geuru.h
OBJ=src/stack.o src/atom.o geuru.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

geuru: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -g -Wall