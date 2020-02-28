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
#include <pthread.h>

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

#define MAX_CLIENTS 10

typedef struct client_data {
	int socket;
	long unsigned int tid;
} client_data_t;

client_data_t clients_data[MAX_CLIENTS];

void* on_client_connected(void *client_data_p) {
	client_data_t *client_data = client_data_p;

	uint16_t number = receive_sint(client_data->socket);

	for (uint16_t i = 1; i <= number; i++) {
		if (number % i == 0) {
			send_sint(client_data->socket, i);
		}
	}

	send_sint(client_data->socket, 0);

	close(client_data->socket);
}

void wait_for_connection(int server_socket, thread_connected_callback cb) {
	int number_of_clients = 0;

	while (1) {
		client_data_t *client_data;
		struct sockaddr_in client;
		int client_socket;
		int size = sizeof(client);

		memset(&client, 0, size);

		client_socket = accept(server_socket, (struct sockaddr *) &client, &size);

		if (number_of_clients == MAX_CLIENTS) {
			for (int i = 0; i < MAX_CLIENTS; i++) {
				client_data = &clients_data[i];
				pthread_join(client_data->tid, NULL);
			}

			number_of_clients = 0;
		}

		client_data = &clients_data[number_of_clients];
		client_data->socket = client_socket;

		pthread_create(&client_data->tid, NULL, cb, client_data);

		number_of_clients++;

		printf("number_of_clients: %d\n", number_of_clients);
	}
}

int main() {
	struct sockaddr_in server;

	int server_socket = init_server(&server);
	if (server_socket < 0) {
		return 0;
	}

	wait_for_connection(server_socket, on_client_connected);
}
