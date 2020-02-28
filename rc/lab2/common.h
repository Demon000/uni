#ifndef SERVER_PORT
#define SERVER_PORT 1234
#endif

#ifndef SERVER_ADDRESS
#define SERVER_ADDRESS "127.0.0.1"
#endif

#define SOCKET_BACKLOG 5

typedef void (*connected_callback)(int socket);
typedef void* (*thread_connected_callback)(void *data);

void send_sint(int socket, uint16_t number) {
	uint16_t network_number = htons(number);
	send(socket, &network_number, sizeof(network_number), 0);
}

uint16_t receive_sint(int socket) {
	uint16_t network_number;
	recv(socket, &network_number, sizeof(network_number), MSG_WAITALL);
	return ntohs(network_number);
}

void send_string(int socket, char *string) {
	uint16_t length = strlen(string) + 1;

	send_sint(socket, length);

	for (int i = 0; i < length; i++) {
		send(socket, &string[i], sizeof(char), 0);
	}
}

void receive_string(int socket, char *string) {
	uint16_t length;

	length = receive_sint(socket);

	for (int i = 0; i < length; i++) {
		recv(socket, &string[i], sizeof(char), MSG_WAITALL);
	}
}

void receive_string_line(int socket, char* string) {
	size_t size = 0;

	while (1) {
		recv(socket, &string[size], sizeof(char), MSG_WAITALL);
		if (string[size] == '\n') {
			size++;
			break;
		}
		size++;
	}

	string[size] = '\0';
}

void send_string_line(int socket, char* string) {
	uint16_t length = strlen(string);
	char line_terminator = '\n';

	for (int i = 0; i < length; i++) {
		send(socket, &string[i], sizeof(char), 0);
	}

	send(socket, &line_terminator, sizeof(char), 0);
}
