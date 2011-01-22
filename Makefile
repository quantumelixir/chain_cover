CC=cc
CFLAGS=-Wall -Werror

OBJECTS=random_matrix.o chain.o graph.o vertex.o solve.o read_input.o

chaincover: main.c $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

.o: .c
