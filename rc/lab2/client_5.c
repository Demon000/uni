#define SERVER_ADDRESS "192.168.43.201"
#define SERVER_PORT 5565

#include "client.h"

void on_connected(int server_socket) {
	uint16_t number;
	uint16_t number_of_divisors;

	printf("Connected successfully\n");

	printf("number: ");
	scanf("%hu", &number);
	send_sint(server_socket, number);

	number_of_divisors = receive_sint(server_socket);
	for (int i = 0; i < number_of_divisors; i++) {
		number = receive_sint(server_socket);
		printf("%d ", number);
	}
	printf("\n");
}

int main() {
	struct sockaddr_in server;

	init_server_connection(&server, on_connected);
}
