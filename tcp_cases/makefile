CC = gcc
CFLAGS = -g -Wall -Werror -std=c99
objects = timeout.o
build: server.bin client.bin
server.bin: server.o
	$(CC) -o server.bin $(CFLAGS) server.o
client.bin: client.o
	$(CC) -o client.bin $(CFLAGS) client.o
server: utils.h
client: utils.h
clean:
	rm -rf *.o *.bin
