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
	struct sockaddr_in server;
	uint16_t a, b, suma;
	int c;

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(SERVER_PORT);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Error creating client socket\n");
		return 1;
	}

	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Error connecting to server\n");
		return 1;
	}

	printf("a = ");
	scanf("%hu", &a);
	printf("b = ");
	scanf("%hu", &b);
	a = htons(a);
	b = htons(b);

	send(c, &a, sizeof(a), 0);
	send(c, &b, sizeof(b), 0);
	recv(c, &suma, sizeof(suma), 0);

	suma = ntohs(suma);

	printf("Suma este %hu\n", suma);

	close(c);
}
