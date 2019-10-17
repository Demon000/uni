#include "server.h"

void merge_strings(char *first, char *second, char *result) {
	int first_length = strlen(first);
	int second_length = strlen(second);
	int result_length = first_length + second_length;
	int first_index = 0;
	int second_index = 0;
	int result_index = 0;

	while (result_index  < result_length) {
		if (first_index < first_length
				&& first[first_index] < second[second_index]
				|| second_index >= second_length) {
			result[result_index++] = first[first_index++];
		} else if (second_index < second_length
				&& second[second_index] < first[first_index]
				|| first_index >= first_length) {
			result[result_index++] = second[second_index++];
		} else {
			break;
		}
	}

	result[result_index++] = '\0';
}

void on_client_connected(int client_socket) {
	char first[256];
	char second[256];
	char result[512];

	printf("A client has connected\n");

	receive_string(client_socket, first);
	receive_string(client_socket, second);
	merge_strings(first, second, result);

	send_string(client_socket, result);
}

int main() {
	struct sockaddr_in server;

	server_socket = init_server(&server);
	if (server_socket < 0) {
		return 0;
	}

	wait_for_connection(server_socket, on_client_connected);
}
