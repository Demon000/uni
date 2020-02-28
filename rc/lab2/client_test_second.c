#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 1234

#include "client.h"

void on_connected(int server_socket) {
	uint16_t number;
	uint16_t number_of_divisors;

	printf("Connected successfully\n");

	printf("number: ");
	scanf("%hu", &number);
	send_sint(server_socket, number);

	printf("divisors:\n");
	while (1) {
		number = receive_sint(server_socket);
		if (number == 0) {
			break;
		}

		printf("%hu\n", number);
	}
}

int main() {
	struct sockaddr_in server;

	init_server_connection(&server, on_connected);
}
