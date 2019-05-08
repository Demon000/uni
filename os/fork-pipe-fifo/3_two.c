#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
	int fd = open("three_fifo", O_RDONLY);

	int no_digits = 0;
	int no_lowercase = 0;
	int no_uppercase = 0;
	char message[102];
	int i = 0;
	char c;

	read(fd, message, 102);

	while (1) {
		c = message[i];

		if ('0' <= c && c <= '9') {
			no_digits++;
		} else if ('a' <= c && c <= 'z') {
			no_lowercase++;
		} else if ('A' <= c && c <= 'Z') {
			no_uppercase++;
		} else if (c == '\0') {
			break;
		}

		i++;
	}

	printf("digits: %d\n"
			"lowecase: %d\n"
			"uppercase %d\n",
			no_digits,
			no_lowercase,
			no_uppercase);

	return 0;
}
