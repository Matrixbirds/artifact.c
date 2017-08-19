CC := gcc
CFLAGS := -g -Wall -Werror -std=c99
objects := artifact.o repl.o
artifact.o: repl.h
repl.bin: $(objects)
	$(CC) -o repl.bin $(CFLAGS) $(objects)
clean:
	rm -rf *.{bin, o}
