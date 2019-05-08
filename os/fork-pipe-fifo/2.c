#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int print_divisors(int n) {
	for (int divisor = 2; divisor < n; divisor++) {
		if (n % divisor == 0) {
			printf("%d ", divisor);
		} 
	}

	printf("\n");
}

int main() {
	int p_one_two[2];
	int p_one_three[2];
	int p_parent_three[2];
	int p_two_three[2];

	pipe(p_one_two);
	pipe(p_one_three);
	pipe(p_two_three);
	pipe(p_parent_three);

	int pid;

	pid = fork();
	if (pid == 0) {
		int n_write;

		close(p_one_two[0]);
		close(p_one_three[0]);

		printf("Number: ");
		scanf("%d", &n_write);
		write(p_one_two[1], &n_write, sizeof(n_write));
		write(p_one_three[1], &n_write, sizeof(n_write));

		close(p_one_two[1]);
		close(p_one_three[1]);

		exit(0);
	}

	pid = fork();
	if (pid == 0) {
		int n_one_read;
		int temp_write = 1;

		close(p_one_two[1]);
		close(p_two_three[0]);

		read(p_one_two[0], &n_one_read, sizeof(n_one_read));
		print_divisors(n_one_read);

		write(p_two_three[1], &temp_write, sizeof(temp_write));

		close(p_one_two[0]);
		close(p_two_three[1]);
		exit(0);
	}

	pid = fork();
	if (pid == 0) {
		int n_two_read;
		int no_numbers_write;
		int number_write;
		int temp_read;

		close(p_one_three[1]);
		close(p_two_three[1]);
		close(p_parent_three[0]);

		read(p_two_three[0], &temp_read, sizeof(temp_read));

		read(p_one_three[0], &n_two_read, sizeof(n_two_read));

		no_numbers_write = n_two_read / 3;

		write(p_parent_three[1], &no_numbers_write, sizeof(no_numbers_write));

		printf("%d numbers: ", no_numbers_write);
		while (no_numbers_write) {
			scanf("%d", &number_write);

			write(p_parent_three[1], &number_write, sizeof(number_write));

			no_numbers_write--;
		}

		close(p_one_three[0]);
		close(p_two_three[0]);
		close(p_parent_three[1]);
		exit(0);
	}

	wait(0);
	wait(0);
	wait(0);

	int no_numbers_read;
	int number_read;
	int sum = 0;
	float average;

	close(p_parent_three[1]);

	read(p_parent_three[0], &no_numbers_read, sizeof(no_numbers_read));

	for (int i = 0; i < no_numbers_read; i++) {
		read(p_parent_three[0], &number_read, sizeof(number_read));

		sum += number_read;
	}
	
	average = (float) sum / no_numbers_read;

	printf("%f\n", average);

	close(p_parent_three[0]);

	return 0;
}
