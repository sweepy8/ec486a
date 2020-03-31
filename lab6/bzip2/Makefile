CC=gcc
CFLAGS=-O0

SPEC_FLAGS=-DSPEC_CPU

all:
	$(CC) $(CFLAGS) $(SPEC_FLAGS) -c blocksort.c
	$(CC) $(CFLAGS) $(SPEC_FLAGS)  -c bzip2.c
	$(CC) $(CFLAGS) $(SPEC_FLAGS) -c bzlib.c
	$(CC) $(CFLAGS) $(SPEC_FLAGS) -c compress.c
	$(CC) $(CFLAGS) $(SPEC_FLAGS) -c crctable.c
	$(CC) $(CFLAGS) $(SPEC_FLAGS) -c decompress.c
	$(CC) $(CFLAGS) $(SPEC_FLAGS) -c huffman.c
	$(CC) $(CFLAGS) $(SPEC_FLAGS) -c randtable.c
	$(CC) $(CFLAGS) $(SPEC_FLAGS) -c spec.c
	$(CC) -o bzip2 blocksort.o bzip2.o bzlib.o compress.o crctable.o decompress.o huffman.o randtable.o spec.o

clean:
	rm -f *.o bzip2
