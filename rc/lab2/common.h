#define SERVER_PORT 1234
#define SERVER_ADDRESS "127.0.0.1"
#define SOCKET_BACKLOG 5

typedef void (*connected_callback)(int socket);

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

char* receive_string(int socket, char *string) {
	uint16_t length;

	length = receive_sint(socket);

	for (int i = 0; i < length; i++) {
		recv(socket, &string[i], sizeof(char), MSG_WAITALL);
	}

	return string;
}
