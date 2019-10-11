#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "client_server_common.h"

int main() {
	struct sockaddr_in server, client;
	int c, l;
	int s;

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(SERVER_PORT);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Error creating server socket\n");
		return 1;
	}

	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Error binding server socket\n");
		return 1;
	}

	listen(s, SOCKET_BACKLOG);

	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while (1) {
		uint16_t a, b, suma;
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("A client has connected\n");

		recv(c, &a, sizeof(a), MSG_WAITALL);
		recv(c, &b, sizeof(b), MSG_WAITALL);

		a = ntohs(a);
		b = ntohs(b);
		suma = a + b;
		suma = htons(suma);

		send(c, &suma, sizeof(suma), 0);

		close(c);
	}
}
