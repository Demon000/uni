#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "common.h"

int init_server(struct sockaddr_in *server) {
	int server_socket;
	int value = 1;
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

	rc = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
	if (rc < 0) {
		printf("Error setting socket reuse option\n");
		return rc;
	}

	rc = bind(server_socket, (struct sockaddr *) server, sizeof(*server));
	if (rc < 0) {
		printf("Error binding server socket\n");
		return rc;
	}

	listen(server_socket, SOCKET_BACKLOG);

	return server_socket;
}

void wait_for_connection(int server_socket, connected_callback cb) {
	while (1) {
		struct sockaddr_in client;
		int client_socket;
		int size = sizeof(client);

		memset(&client, 0, size);

		client_socket = accept(server_socket, (struct sockaddr *) &client, &size);

		if (fork() == 0) {
			cb(client_socket);
			close(client_socket);
		}
	}
}
