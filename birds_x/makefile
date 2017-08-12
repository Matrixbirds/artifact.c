CC = gcc
CFLAGS = -g -Wall -Werror -std=c99
objects = main.o server.o util.o
app: $(objects)
	$(CC) -o app $(CFLAGS) $(objects)
main.o: server.h defs.h
server.o: server.h defs.h
clean:
	rm -rf *.o app
