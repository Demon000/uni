#define SERVER_PORT 8877
#define SERVER_ADDRESS "172.30.3.1"

#include "client.h"

void on_connected(int server_socket) {
	char message[1024];
	receive_string_line(server_socket, message);
	printf("%s\n", message);

	send_string_line(server_socket, "Tanislav Cosmin-Gabriel");
	receive_string_line(server_socket, message);
	printf("%s\n", message);

	send_string_line(server_socket, "12");
	receive_string_line(server_socket, message);
	printf("%s\n", message);

	send_string_line(server_socket, "y");
	receive_string_line(server_socket, message);
	printf("%s\n", message);
}

int main() {
	struct sockaddr_in server;

	init_server_connection(&server, on_connected);
}
