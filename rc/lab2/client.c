#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "client_server_common.h"

int init_server(struct sockaddr_in *server) {
	int server_socket;
	int rc;

	memset(server, 0, sizeof(*server));
	server->sin_port = htons(SERVER_PORT);
	server->sin_family = AF_INET;
	server->sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		printf("Error creating client socket\n");
		return server_socket;
	}

	rc = connect(server_socket, (struct sockaddr *) server, sizeof(*server));
	if (rc < 0) {
		printf("Error connecting to server\n");
		return rc;
	}

	return server_socket;
}

void on_connected(int server_socket) {
	printf("Connected successfully\n");

	uint16_t a, b, suma;
	printf("a = ");
	scanf("%hu", &a);
	printf("b = ");
	scanf("%hu", &b);
	a = htons(a);
	b = htons(b);

	send(server_socket, &a, sizeof(a), 0);
	send(server_socket, &b, sizeof(b), 0);
	recv(server_socket, &suma, sizeof(suma), 0);

	suma = ntohs(suma);

	printf("The sum is %hu\n", suma);
}

int main() {
	struct sockaddr_in server;
	int server_socket;

	server_socket = init_server(&server);
	if (server_socket < 0) {
		return 0;
	}

	on_connected(server_socket);
	close(server_socket);
}
