CC = gcc
CFLAGS = -g -Wall -Werror -std=c99
build_tcp: tcp_server.bin tcp_client.bin raw_socket.bin
raw_socket.bin: raw_socket_client.o
	$(CC) -o raw_socket.bin $(CFLAGS) raw_socket_client.o
tcp_server.bin: tcp_server.o
	$(CC) -o tcp_server.bin $(CFLAGS) tcp_server.o
tcp_client.bin: tcp_client.o
	$(CC) -o tcp_client.bin $(CFLAGS) tcp_client.o
raw_socket_client: defs.h
tcp_server: utils.h
tcp_client: utils.h
clean:
	rm -rf *.o *.bin
