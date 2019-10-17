#include "client.h"

void on_connected(int server_socket) {
	char first[256];
	char second[256];
	char result[512];

	printf("Connected successfully\n");

	printf("first string: ");
	scanf("%s", first);
	send_string(server_socket, first);

	printf("second string: ");
	scanf("%s", second);
	send_string(server_socket, second);

	receive_string(server_socket, result);
	printf("merged string: %s\n", result);
}

int main() {
	struct sockaddr_in server;

	init_server_connection(&server, on_connected);
}
