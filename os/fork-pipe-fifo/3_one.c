#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
	char message[102];
	int fd;

	printf("Message: ");
	fgets(message, 101, stdin);

	mkfifo("three_fifo", 0644);

	fd = open("three_fifo", O_WRONLY);

	write(fd, message, 102);

	return 0;
}
