CC = gcc
CFLAGS = -g -Wall -Werror -std=c99
objects = main.o hahs.o
build: main.bin
main.o: hahs.h
main.bin: $(objects)
	$(CC) -o main.bin $(CFLAGS) $(objects)
clean:
	rm -rf *.o *.bin
