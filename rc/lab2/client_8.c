#include "client.h"
#include <inttypes.h>

void on_connected(int server_socket) {
	uint16_t length;
	uint16_t number;

	printf("Connected successfully\n");

	printf("first numbers length: ");
	scanf("%hu", &length);

	send_sint(server_socket, length);

	while (length > 0) {
		printf("number: ");
		scanf("%hu", &number);
		send_sint(server_socket, number);
		length--;
	}

	printf("second numbers length: ");
	scanf("%hu", &length);
	send_sint(server_socket, length);

	while (length > 0) {
		printf("number: ");
		scanf("%hu", &number);
		send_sint(server_socket, number);
		length--;
	}

	length = receive_sint(server_socket);
	while (length > 0) {
		number = receive_sint(server_socket);
		printf("%hu ", number);
		length--;
	}
	printf("\n");
}

int main() {
	struct sockaddr_in server;

	init_server_connection(&server, on_connected);
}
