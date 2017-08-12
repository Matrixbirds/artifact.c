CC = gcc
CFLAGS = -g -Wall -std=c99
objects = main.o server.o util.o
app: $(objects)
	$(CC) -o app $(CFLAGS) $(objects)
main.o: server.h defs.h util.h
server.o: server.h defs.h util.h
clean:
	rm -rf *.o app
