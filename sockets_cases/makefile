CC = gcc
CFLAGS = -g -Wall -Werror -std=c99
build_tcp: tcp_server.bin tcp_client.bin
tcp_server.bin: tcp_server.o
	$(CC) -o tcp_server.bin $(CFLAGS) tcp_server.o
tcp_client.bin: tcp_client.o
	$(CC) -o tcp_client.bin $(CFLAGS) tcp_client.o
tcp_server: utils.h
tcp_client: utils.h
clean:
	rm -rf *.o *.bin
