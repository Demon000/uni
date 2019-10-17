#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "common.h"

int init_server_connection(struct sockaddr_in *server, connected_callback cb) {
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

	cb(server_socket);

	close(server_socket);
}
