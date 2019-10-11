#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "client_server_common.h"

typedef void (*client_connected_callback)(int client_socket);

int init_server(struct sockaddr_in *server) {
	int server_socket;
	int rc;

	memset(server, 0, sizeof(*server));
	server->sin_port = htons(SERVER_PORT);
	server->sin_family = AF_INET;
	server->sin_addr.s_addr = INADDR_ANY;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		printf("Error creating server socket\n");
		return server_socket;
	}

	rc = bind(server_socket, (struct sockaddr *) server, sizeof(*server));
	if (rc < 0) {
		printf("Error binding server socket\n");
		return rc;
	}

	listen(server_socket, SOCKET_BACKLOG);

	return server_socket;
}

void wait_for_connection(int server_socket, client_connected_callback cb) {
	while (1) {
		struct sockaddr_in client;
		int client_socket;
		int size = sizeof(client);

		memset(&client, 0, size);

		client_socket = accept(server_socket, (struct sockaddr *) &client, &size);

		cb(client_socket);
		close(client_socket);
	}
}

void on_client_connected(int client_socket) {
	printf("A client has connected\n");

	uint16_t a, b, suma;
	recv(client_socket, &a, sizeof(a), MSG_WAITALL);
	recv(client_socket, &b, sizeof(b), MSG_WAITALL);

	a = ntohs(a);
	b = ntohs(b);
	suma = a + b;
	suma = htons(suma);

	send(client_socket, &suma, sizeof(suma), 0);
}

int main() {
	struct sockaddr_in server;
	int server_socket;

	server_socket = init_server(&server);
	if (server_socket < 0) {
		return 0;
	}

	wait_for_connection(server_socket, on_client_connected);
}
