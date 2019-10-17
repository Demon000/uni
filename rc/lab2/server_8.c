#include "server.h"

void on_client_connected(int client_socket) {
	uint16_t *first;
	uint16_t *second;
	uint16_t *result;
	uint16_t first_length;
	uint16_t second_length;
	uint16_t max_result_length;
	uint16_t result_length = 0;

	printf("A client has connected\n");

	first_length = receive_sint(client_socket);
	printf("%d\n", first_length);
	first = malloc(first_length * sizeof(uint16_t));

	for (int i = 0; i < first_length; i++) {
		first[i] = receive_sint(client_socket);
	}

	second_length = receive_sint(client_socket);
	printf("%d\n", second_length);
	second = malloc(first_length * sizeof(uint16_t));

	for (int i = 0; i < second_length; i++) {
		second[i] = receive_sint(client_socket);
	}

	max_result_length = first_length > second_length ? first_length : second_length;
	printf("%d\n", max_result_length);
	result = malloc(max_result_length * sizeof(uint16_t));

	for (int i = 0; i < first_length; i++) {
		uint16_t first_number = first[i];
		for (int j = 0; j < second_length; j++) {
			uint16_t second_number = second[j];
			if (first_number == second_number) {
				result[result_length++] = first_number;
				break;
			}
		}
	}

	send_sint(client_socket, result_length);
	for (int i = 0; i < result_length; i++) {
		send_sint(client_socket, result[i]);
	}
}
int main() {
	struct sockaddr_in server;

	server_socket = init_server(&server);
	if (server_socket < 0) {
		return 0;
	}

	wait_for_connection(server_socket, on_client_connected);
}
