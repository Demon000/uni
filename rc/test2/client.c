#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int c;
    struct sockaddr_in server;

    c = socket(AF_INET, SOCK_DGRAM, 0);
    if (c < 0) {
        printf("Eroare la crearea socketului client\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    int server_size = sizeof(server);

    char end_char;
    printf("end_char: ");
    scanf("%c", &end_char);
    sendto(c, &end_char, sizeof(end_char), 0, (struct sockaddr *) &server, server_size);

    char message[256];
    printf("message: ");
    scanf("%s", message);
    int message_length = strlen(message) + 1;
    sendto(c, &message_length, sizeof(message_length), 0, (struct sockaddr *) &server, server_size);
    sendto(c, message, message_length, 0, (struct sockaddr *) &server, server_size);

    int recv_message_length;
    recvfrom(c, &recv_message_length, sizeof(recv_message_length), MSG_WAITALL, (struct sockaddr *)&server, &server_size);
    printf("recv_message_length: %d\n", recv_message_length);

    printf("recv_message: ");
    char recv_char;
    for (int i = 0; i < recv_message_length; i++) {
        recvfrom(c, &recv_char, sizeof(recv_char), MSG_WAITALL, (struct sockaddr *)&server, &server_size);
        printf("%c", recv_char);
    }

    recvfrom(c, &recv_char, sizeof(recv_char), MSG_WAITALL, (struct sockaddr *)&server, &server_size);
    printf("%c", recv_char);
    printf("\n");

    close(c);
}
