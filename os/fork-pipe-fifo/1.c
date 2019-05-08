#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int p[2];
	int pid;

	pipe(p);

	pid = fork();
	if (pid == 0) {
		char input_message[102];

		close(p[0]);
		printf("Input: ");
		fgets(input_message, 102, stdin);
		printf("1 -> read from stdin: %s\n", input_message);
		write(p[1], input_message, 101);
		close(p[1]);
		exit(0);
	}

	pid = fork();
	if (pid == 0) {
		char output_message[102];
		char c;

		int i = 0;
		int no_digits = 0;
		int no_lowercase = 0;
		int no_uppercase = 0;

		close(p[1]);
		read(p[0], output_message, 102);
		printf("2 -> read from other child: %s\n", output_message);

		while (1) {
			c = output_message[i];

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

		close(p[0]);
		exit(0);
	}

	wait(0);
	wait(0);

	return 0;
}
