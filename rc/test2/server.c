#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int s;
    struct sockaddr_in server;
    time_t seconds;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        printf("Eroare la crearea socketului server\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr * ) & server, sizeof(server)) < 0) {
        printf("Eroare la bind\n");
        return 1;
    }

    struct sockaddr_in client;
    int client_size = sizeof(client);
    memset(&client, 0, client_size);

    char end_char;
    recvfrom(s, &end_char, sizeof(end_char), MSG_WAITALL, (struct sockaddr *)&client, &client_size);
    printf("end_char: %c\n", end_char);

    int message_length;
    recvfrom(s, &message_length, sizeof(message_length), MSG_WAITALL, (struct sockaddr *)&client, &client_size);
    printf("message_length: %d\n", message_length);

    char *message = malloc(message_length * sizeof(*message));
    recvfrom(s, message, message_length, MSG_WAITALL, (struct sockaddr *)&client, &client_size);
    printf("message: %s\n", message);

    int sent_message_length;
    for (sent_message_length = message_length; sent_message_length > 0; sent_message_length--) {
        if (message[sent_message_length] == end_char) {
            break;
        }
    }

    printf("sent_message_length: %d\n", sent_message_length);
    sendto(s, &sent_message_length, sizeof(sent_message_length), 0, (struct sockaddr *) &client, client_size);

    // sent_message_length++;
    // sendto(s, &sent_message_length, sizeof(sent_message_length), 0, (struct sockaddr *) &client, client_size);
    //
    // char *sent_message = malloc(sent_message_length * sizeof(char));
    // strncpy(sent_message, message, sent_message_length);
    // sent_message[sent_message_length] = '\0';
    // sendto(s, sent_message, sent_message_length * sizeof(*sent_message), 0, (struct sockaddr *) &client, client_size);

    char sent_char;
    for (int i = 0; i < sent_message_length; i++) {
        sent_char = message[i];
        sendto(s, &sent_char, sizeof(sent_char), 0, (struct sockaddr *) &client, client_size);
    }
    sent_char = '\0';
    sendto(s, &sent_char, sizeof(sent_char), 0, (struct sockaddr *) &client, client_size);

    close(s);
}
